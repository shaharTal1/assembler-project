#include "Pre-assembler.h"

/**
 * builds a new file with macros layout, without their definitions and without comment lines.
 * @param 
 */
FILE * pre_assembler( FILE * file,char *fileNmae)
{
    int inDefinition=0; /*A flag that indicates whether we are reading a macro or not*/
    char line[MAX_LINE];/* an array that contine a line from the orignal file */
    FILE *macroFile;/* a pointer to the new file */
    Line *expandedLine;
    Line *tempFoFree;
    macro *list = new_macro(NULL,NULL);/* list o f macros */
    macro *temp ;
    char buf[255];/* buffer for the function sprintf ,in size of the maximum size of file's name */
    

    sprintf(buf,"%s.am",fileNmae);
    macroFile=fopen(buf,"w+");/* open a new file with end of .am*/
    check(macroFile,"file");

    while(fgets(line,MAX_LINE,file))
    {
        expandedLine=get_word(line," ",0);/* get the first word in the line */

        /* if its a comment line */
        if(strcmp(expandedLine->word,COMMENT)==0)
            continue;

        while (expandedLine->word)
        {
            /* if its the end of the defintion of the macro */
            if((strcmp(expandedLine->word ,ENDM)==0) && (inDefinition==1)){
                inDefinition = 0;
                expandedLine = get_word(expandedLine->rest," ",0);
                continue;
            }

            /* if we are in a middle of macro*/
            else if((inDefinition==1))
            {
                insert_text(list,expandedLine->word);
                if(expandedLine->endLine==1)
                    insert_text(list,"\n");
            }
        
            /* if the word is a macro's name */
            else if(inDefinition==0 && (temp = macro_name(expandedLine->word,list)))
            {
                printf("macro name ->%s\n",temp->name);
                macroFile = print_content(macroFile,temp);
                expandedLine = get_word(expandedLine->rest," ",0);/* get the next word in the line */
                continue;
            }

            /* If there is a start of macro definition */
            else if(strcmp(expandedLine->word,MACRO)==0)
            {
                expandedLine = get_word(expandedLine->rest," ",0);/* get the next word in the line */
                list = new_macro(list,expandedLine->word);/* creat a new macro in the list */

                if(expandedLine->rest && (strcmp(expandedLine->rest,"\n")!=0))
                    insert_text(list, expandedLine->rest);
                
                inDefinition = 1;
                break;
            }

            else fprintf(macroFile,"%s ",expandedLine->word);
            tempFoFree=expandedLine;
            expandedLine=get_word(expandedLine->rest," ",0);/*get the next word in the line */
            free(tempFoFree);/* free the prev line */
        }
        if(inDefinition == 0)
            fprintf(macroFile,"\n");
    }
    free_list(list);
    return macroFile;
}

/* insert the text in the definition into the macro's text */
void insert_text (macro *m,char *text)
{
    printf("name : %s \ntext : %s\n ------\n", m->name, m->text);
    if(text)
    {
        /* uf its the first word in the macro's text*/
        if(!m->text)
        {
            m->text = (char *)malloc((strlen(text)+1+1)*sizeof(char));/* add 1 for EOF and another 1 for space*/
            check(m->text,"malloc");
            strcpy(m->text,text);/* add the text to the macro text*/
            strcat(m->text," ");/* add a space between words*/
        }
        else
        {
            m->text = (char *)realloc(m->text,(sizeof(char)*(strlen(m->text)+strlen(text)+1+1)));/* add 1 for EOF and another 1 for space*/
            check(m->text,"realloc");
            strcat(m->text,text);/* add the new text */
            strcat(m->text," ");/* add a space between words*/
        }
    }
}

/*goes through the list and checks if there is a macro of like the word sent to the function */
macro * macro_name ( char *word, macro * head)
{
    macro *p;
    p = head;

    while( p && p->name)
    {
       /* printf("macro name-%s word -%s\n",p->name,word);*/
        if(strcmp(word,p->name)==0)
            return p;
        
        p = p->next;
    }
    return NULL;
}

/* print the content of the macro insted of the macro name*/
FILE * print_content(FILE * file, macro *m)
{
    fprintf(file,"%s",m->text); /* print the macro content in to the new file */
    return file;
    
}

int main(int argc, char *argv[])
{
    FILE *fp;
    fp=fopen(argv[1],"r");
    if(!fp){
        printf("error somthing hepend \n");
        exit(1);
    }
    pre_assembler(fp,argv[1]);
    return 0;

}
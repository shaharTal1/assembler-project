#include "Pre-assembler.h"

/* get a line and insert to LINE the first word and the rest using strtok */
Line *get_word(char line[], char *skip,int lineNumber)
{
    char *pword;
    char *prest;

    Line *newLine = new_line();

    if(line){
        pword = strtok(line, skip);/* separate the first word from the rest of the line */
        prest = strtok(NULL,"");/* get the rest*/
        
        /*if there is only one part in the line*/
        if (prest == NULL && strlen(pword) > 0)
        {
            newLine->endLine = 1;
            pword[strlen(pword) - 1] = '\0';
        }

        newLine->word = pword;
        newLine->rest = prest;
    }
    else {
        newLine->rest = NULL;
        newLine->word = NULL;
    }
    newLine->lineNumber = lineNumber;
    return newLine; /* return the expended line*/
}

/**function gets pointer and type of action done before,
 * accordingly prints the appropriate error in case of need*/
int check(void * toCheck, char *type)
{
    if(!toCheck)/* if the pointer is null for some reason*/
    {
        if(strcmp(type,"file")==0)
        {
            printf("ERROR :  can not open file :(\n");
            return 0;
        }

        else if(strcmp(type,"malloc")==0)
            printf("ERROR : malloc failure :(\n");
            
        else if(strcmp(type,"calloc")==0)
            printf("ERROR : calloc failure :(\n");

        else if(strcmp(type,"realloc")==0)
            printf("ERROR : realloc failure :(\n");

        exit(1);
    }
    return 0;
}

/* check if the word is a start of a lable */
char *is_lable(char *word)
{
    int length;
    char last;

    /* if the first char is an alphabetic letter*/
    if(((*word)>='A' && (*word)<='Z') || ((*word)>='a' && (*word)<='z'))
    {
        length = strlen(word);
        last = *(word + length);/* get the last char in the word*/

        if(last == ":")
        {
            word[length] = '\0'; /* get rid from the ":" */
            return word; /* return the lable's name */
        }
    }
}
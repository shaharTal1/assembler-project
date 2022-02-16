#include "Pre-assembler.h"
#include "global.h"
/* creat a new macro and add it to the head of the list , 
return a pointer to the new macro in the list */
macro  *new_macro(macro *head, char *name)
{
    macro *newMacro = (macro *)malloc(sizeof(macro));
    check(newMacro,"malloc");/* check if newMacro is ok*/
    if(name)
    {
        newMacro->name = (char *)malloc(sizeof(char)*(strlen(name)+1));
        check(newMacro->name,"malloc");

        strcpy(newMacro->name,name);
    }

    newMacro->next = head;
    newMacro->text = NULL;

    return(newMacro);
}

/*free the list from the mamory */
int free_list(macro *head)
{
    macro *current = head;/* pinter for the head of the list*/
    macro *pnext;
    
    while(current)
    {
        pnext = current->next;
        if(current->text)
            free(current->text);
        if(current->name)
            free(current->name);
        free(current);
        current = pnext;
    }
    return 0;
}

/* make a new line */
Line *new_line()
{
    Line *newLine;
    newLine = (Line *)malloc(sizeof(Line));

   check(newLine,"malloc");

    newLine->endLine=0;

    return newLine;
}

/* creat a new symbol and add it to the head of the list, if the head is NULL it will creat a new list*/
symbol *new_symbol(symbol *head)
{
    symbol *newSymbol = (symbol *)malloc(sizeof(symbol));
    check(newSymbol,"malloc");/*check if the new symbol is ok*/

    newSymbol->next = head;
    newSymbol->name = NULL;
    newSymbol->offset = newSymbol->value = newSymbol->attributes = newSymbol->baseAddress = 0;

    return newSymbol;
}

void free_table(symbol *head)
{
    symbol *current = head;/* pinter for the head of the list*/
    symbol *pnext;
    
    while(current)
    {
        pnext = current->next;
        free(current);
        current = pnext;
    }
    return 0;
}


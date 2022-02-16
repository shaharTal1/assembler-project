#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdalign.h>
#include "global.h"
int IC;
int DC;

/*check if the word is a lable*/
symbol * is_lable(char * word ,symbol * head)
{
    symbol *p;/* point for the head of the list*/
    p = head;

    while( p && p->name)
    {
        if(strcmp(word,head->name)==0)
            return p;
        
        p = p->next;
    }
    return NULL;
}


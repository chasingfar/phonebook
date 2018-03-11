#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phonebook_opt.h"

/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
record *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        for(int i=0;i<INDEX_SIZE;i++){
            if (strcasecmp(lastName, pHead->lastName[i]) == 0)
                return pHead->pRecord[i];
        }
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if(e->length>=INDEX_SIZE){
        e->pNext = (entry *) malloc(sizeof(entry));
        e->length=0;
        e=e->pNext;
        e->pNext=NULL;
    }
    e->pRecord[e->length]=(record *) malloc(sizeof(record));
    strcpy(e->pRecord[e->length]->lastName, lastName);
    strcpy(e->lastName[e->length], lastName);
    e->length++;

    return e;
}

entry *init()
{
    entry *e = (entry *) malloc(sizeof(entry));
    e->length=0;
    e->pNext=NULL;
    printf("size of INDEX : %d\n", INDEX_SIZE);
    return e;
}

void clean(entry *pHead)
{
    if(pHead->pNext)free(pHead->pNext);
    free(pHead);
}

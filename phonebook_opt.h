#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1

#ifndef INDEX_SIZE
#define INDEX_SIZE 1024
#endif

#include "hash.h"

typedef struct __PHONE_BOOK_RECORD {
    char lastName[MAX_LAST_NAME_SIZE];

    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];

} record;

enum __RED_BLACK_TREE_COLOR {RED,BLACK};
typedef struct __RED_BLACK_TREE_NODE {
    struct __RED_BLACK_TREE_NODE *parent;
    struct __RED_BLACK_TREE_NODE *left;
    struct __RED_BLACK_TREE_NODE *right;
    enum __RED_BLACK_TREE_COLOR color;
    HASH_TYPE lastNameHash;
    record* pRecord;
} node;
typedef struct __PHONE_BOOK_ENTRY {
    node* tree;
} entry;
void insert_check(node *n);
record *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);

entry *init();
void clean(entry *pHead);

#endif

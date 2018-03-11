#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT 1

#ifndef INDEX_SIZE
#define INDEX_SIZE 1024
#endif

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
typedef struct __PHONE_BOOK_ENTRY {
    int length;
    char lastName[INDEX_SIZE][MAX_LAST_NAME_SIZE];
    record *pRecord[INDEX_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;

record *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);

entry *init();
void clean(entry *pHead);

#endif

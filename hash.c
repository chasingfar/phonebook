#include "hash.h"

HASH_TYPE hash(char *str)//djb2 hash
{
    unsigned char *ustr=(unsigned char *)str;
    unsigned long hash = 5381;
    int c;

    while (c = *ustr++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
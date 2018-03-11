#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phonebook_opt.h"

/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
record *findName(char lastName[], entry *pHead)
{
    node *n = pHead->tree;
    HASH_TYPE lastNameHash = hash(lastName);
    while (n != NULL) {
        if (lastNameHash == n->lastNameHash) {
            return n->pRecord;
        } else if (lastNameHash < n->lastNameHash) {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{

    node **n = &e->tree;
    HASH_TYPE lastNameHash = hash(lastName);
    while (*n != NULL) {
        if (lastNameHash == (*n)->lastNameHash) {
            return e;
        } else if (lastNameHash < (*n)->lastNameHash) {
            n = &(*n)->left;
        } else {
            n = &(*n)->right;
        }
    }

    *n = (node *) malloc(sizeof(node));
    (*n)->lastNameHash = lastNameHash;
    (*n)->pRecord = (record *) malloc(sizeof(record));
    strcpy((*n)->pRecord->lastName, lastName);
    insert_check(*n);

    return e;
}

entry *init()
{
    entry *e = (entry *) malloc(sizeof(entry));
    e->tree = NULL;
    return e;
}

void clean(entry *e)
{
    if (e->tree)free(e->tree);
    free(e);
}


/*
 * code below is from Wikipedia red black tree
 * https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
 * */



node *parent(node *n)
{
    return n->parent;
}

node *grandparent(node *n)
{
    node *p = parent(n);
    if (p == NULL)
        return NULL; // No parent means no grandparent
    return parent(p);
}

node *sibling(node *n)
{
    node *p = parent(n);
    if (p == NULL)
        return NULL; // No parent means no sibling
    if (n == p->left)
        return p->right;
    else
        return p->left;
}

node *uncle(node *n)
{
    node *p = parent(n);
    node *g = grandparent(n);
    if (g == NULL)
        return NULL; // No grandparent means no uncle
    return sibling(p);
}

void rotate_left(node *n)
{
    node *nnew = n->right;
    //assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
    n->right = nnew->left;
    nnew->left = n;
    nnew->parent = n->parent;
    n->parent = nnew;
    // (the other related parent and child links would also have to be updated)
}

void rotate_right(node *n)
{
    node *nnew = n->left;
    //assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
    n->left = nnew->right;
    nnew->right = n;
    nnew->parent = n->parent;
    n->parent = nnew;
    // (the other related parent and child links would also have to be updated)
}

void insert_check(node *n)
{
    if (n->parent == NULL) {
        n->color = BLACK;
    } else if (n->parent->color == BLACK) {
        return;
    } else if (uncle(n) != NULL && uncle(n)->color == RED) {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
        insert_check(grandparent(n));
    } else {
        if (n == n->parent->right && n->parent == grandparent(n)->left) {
            rotate_left(n->parent);
            n = n->left;
        } else if (n == n->parent->left && n->parent == grandparent(n)->right) {
            rotate_right(n->parent);
            n = n->right;
        }
        n->parent->color = BLACK;
        grandparent(n)->color = RED;
        if (n == n->parent->left && n->parent == grandparent(n)->left) {
            rotate_right(grandparent(n));
        } else {
            rotate_left(grandparent(n));
        }
    }
}

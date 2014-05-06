#ifndef LLIST_HEADER
#define LLIST_HEADER

#include <stdlib.h>

typedef struct lnode
{
  struct lnode *next;
  void *value;
} lnode;

typedef struct llist
{
  lnode *root;
} llist;

llist *llist_new();
lnode *lnode_new(void *value);

lnode *_llist_insert_rec(lnode*, void*);
void llist_insert(llist*, void*);

lnode *_llist_find_rec(lnode*, void*);
lnode *llist_find(llist*, void*);

lnode *_llist_remove_rec(lnode*, void*, llist*);
void llist_remove(llist*, void*);

int _llist_size_rec(lnode*, int);
int llist_size(llist*);

#endif

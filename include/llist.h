#ifndef LLIST_HEADER
#define LLIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

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

/**
 * Inserts a new node to a linked list
 */
void llist_insert(llist*, void*);

lnode *_llist_find_rec(lnode*, void*);
lnode *llist_find(llist*, void*);

lnode *_llist_remove_rec(lnode*, void*);
void llist_remove(llist*, void*);

void llist_remove_by_index(llist*, int);

int _llist_get_size_rec(lnode*, int);
int llist_get_size(llist*);

lnode *_llist_swap(lnode *, lnode *);

#endif

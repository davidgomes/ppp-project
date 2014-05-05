#include <stdlib.h>

typedef struct
{
  void *root;
} llist;

typedef struct
{
  void *next;
} lnode;

llist *llist_create();

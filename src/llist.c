#include "llist.h"

llist *llist_create()
{
  llist *new_list = (llist*) malloc(sizeof(llist));
  return new_list;
}

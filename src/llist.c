#include "llist.h"

llist *llist_new()
{
  llist *new_list = (llist*) malloc(sizeof(llist));
  return new_list;
}

lnode *lnode_new(void *value)
{
  lnode *new_node = (lnode*) malloc(sizeof(lnode));
  new_node->value = value;
  return new_node;
}

lnode *_llist_insert_rec(lnode *where, void *value)
{
  if (where == NULL)
  {
    where = lnode_new(value);
    return where;
  }

  where->next = _llist_insert_rec(where->next, value);
  return where;
}

void llist_insert(llist *my_llist, void *value)
{
  my_llist->root = _llist_insert_rec(my_llist->root, value);
}

lnode *_llist_find_rec(lnode *where, void *find_value)
{  
  if (where == NULL)
  {
    return NULL;
  }

  if (where->value == find_value)
  {
    return where;
  }

  return _llist_find_rec(where->next, find_value);
}

lnode *llist_find(llist *my_llist, void *value)
{
  return _llist_find_rec(my_llist->root, value);
}

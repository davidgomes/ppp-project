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

lnode *_llist_remove_rec(lnode *where, void *value, llist *list)
{
  if (where == NULL)
  {
    return NULL;
  }

  if (where->value == value)
  {
    list->root = where->next;
    free(where);
    return list->root;
  }

  if (where->next && where->next->value == value) 
  {
    lnode *delete_node = where->next;
    where->next = delete_node->next;  
    free(delete_node);
    return where;
  }

  return _llist_remove_rec(where->next, value, list);
}

void llist_remove(llist *my_llist, void *value)
{
  my_llist->root = _llist_remove_rec(my_llist->root, value, my_llist);
}

int _llist_size_rec(lnode *where, int size)
{
  if (where == NULL)
  {
    return size;
  }

  return  _llist_size_rec(where->next, size + 1);
}

int llist_size(llist *my_llist)
{
  int size = 0;

  return _llist_size_rec(my_llist->root,size);
}

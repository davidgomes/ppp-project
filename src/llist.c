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

void llist_remove(llist *my_llist, void *value)
{
  my_llist->root = _llist_remove_rec(my_llist->root, value);
}

lnode *_llist_remove_rec(lnode *where, void *value)
{
    lnode *current;
    
    current = where;
    
    if (current == NULL)
    {
        return NULL;
    }


    if (current->next && current->next->value == value) // next exists and must be erased
    {
        lnode *deleteNode;
        deleteNode = current->next;
        current->next = deleteNode->next;  // Step 2: reassign current->next ptr
        free (deleteNode);                 // Step 3: delete the node
        return current;
    }

    where->next = _llist_remove_rec(where->next, value);

}

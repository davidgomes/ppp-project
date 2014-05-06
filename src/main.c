#include "main.h"

client *client_find_by_name(lnode *where, char *find_name)
{
  if (where == NULL)
  {
    return NULL;
  }

  if (strcmp(((client*) where->value)->name, find_name) == 0)
  {
    return (client*) where->value;
  }

  return client_find_by_name(where->next, find_name);
}

void main_loop()
{
  int which_option = -1;

  while (which_option != EXIT_OPTION)
  {
    do
    {
      which_option = menu_wait();

      if (which_option == 1)
      {

      }
      else if (which_option == 2)
      {

      }
      else if (which_option == 3)
      {

      }
      else if (which_option == 4)
      {
        client_request_print();
      }
    } while (which_option <= 0);
  }
}

int main()
{
  char david_name[] = "David Gomes";
  client *david = client_create(david_name);
  david->id = 2;

  client_list = llist_new();
  llist_insert(client_list, david);

  client *found = (client*) (llist_find(client_list, david)->value);

  char find_name[] = "David Gomes";

  printf("should be a 2: %d\n", client_find_by_name(client_list->root, find_name)->id);

  menu_load();

  main_loop();

  return 0;
}

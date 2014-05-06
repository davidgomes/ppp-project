#include "main.h"

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
        client_request_print(client_list);
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

  menu_load();
  main_loop();

  return 0;
}

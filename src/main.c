#include "main.h"

int main_loop()
{
  int which_option = -1;

  while (which_option != EXIT_OPTION)
  {
    do {
      which_option = menu_wait();
    } while (which_option <= 0);
  }
}

int main()
{
  client *david = client_create();

  menu_load();

  main_loop();

  return 0;
}

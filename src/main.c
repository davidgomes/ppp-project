#include "main.h"

int main()
{
  menu_load();

  int which_option;
  do {
    which_option = menu_wait();
  } while (which_option <= 0);

  return 0;
}

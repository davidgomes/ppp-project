#include "utils.h"

void get_input(char *say_what, char *save_where, int input_size)
{
  printf("%s", say_what);
  getchar(); // Ugly fix to use fgets
  fgets(save_where, input_size, stdin);
}

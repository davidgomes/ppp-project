#include "utils.h"

void get_str_input(char *say_what, char *save_where, int input_size)
{
  printf("%s", say_what);
  fgets(save_where, input_size, stdin);
  strtok(save_where, "\n");
}

void get_int_input(char *say_what, int *save_where)
{
  char temp_buffer[32];
  printf("%s", say_what);
  fgets(temp_buffer, 32, stdin);
  strtok(temp_buffer, "\n");
  *save_where = atoi(temp_buffer);
}

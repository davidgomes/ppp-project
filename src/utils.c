#include "utils.h"

void clear_screen()
{
  #ifdef WINDOWS
    system("cls");
  #else
    system("clear");
  #endif
}

void get_str_input(char *say_what, char *save_where, int input_size)
{
  printf("%s", say_what);
  fgets(save_where, input_size, stdin);

  strtok(save_where, "\n");
}

void get_int_input(char *say_what, int *save_where)
{
  char temp_buffer[MAX_INT_DIGITS];
  printf("%s", say_what);
  fgets(temp_buffer, MAX_INT_DIGITS, stdin);

  strtok(temp_buffer, "\n");
  *save_where = atoi(temp_buffer);
}

void time_to_str(time_t *which_time, char *save_where)
{
  struct tm *time_info = localtime(which_time);
  strftime(save_where, MAX_TIME_CHARS, "%F", time_info);
}

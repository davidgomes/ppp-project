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

void time_to_str(xtime *which_time, char *save_where)
{
  sprintf(save_where, "%02d/%02d/%04d, às %02d:%02d", which_time->day,
                                                      which_time->month,
                                                      which_time->year,
                                                      which_time->hour,
                                                      which_time->minute);
}

void ask_date(xtime *save_where)
{
  printf("Insira a data que prentende, no formato DD/MM/AAAA HH:MM\n");

  scanf("%d/%d/%d %d:%d", &save_where->day,
                          &save_where->month,
                          &save_where->year,
                          &save_where->hour,
                          &save_where->minute);

  getchar();
}

void time_t_to_xtime(xtime *save_where, time_t *which_time)
{
  struct tm *current_time_info = localtime(which_time);

  save_where->day = current_time_info->tm_mday;
  save_where->month = current_time_info->tm_mon;
  save_where->year = current_time_info->tm_year + 1900;

  save_where->hour = current_time_info->tm_hour;
  save_where->minute = current_time_info->tm_min;
}

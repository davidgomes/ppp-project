#include "xtime.h"

int xtime_smaller(xtime *a, xtime *b) // is a smaller than b
{
  printf("hi\n");

  if (a->year < b->year)
  {
    return 1;
  }
printf("hi2\n");
  if (a->month < b->month)
  {
    return 1;
  }
printf("hi3\n");
  if (a->day < b->day)
  {
    return 1;
  }
printf("hi4\n");
  if (a->hour < b->hour)
  {
    return 1;
  }
printf("hi5\n");
  if (a->minute < b->minute)
  {
    return 1;
  }
printf("hi6\n");
  return 0;
}

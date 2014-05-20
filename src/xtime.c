#include "xtime.h"

int xtime_comp(xtime *a, xtime *b) // returns (a - b)
{
  int a_value = a->year * 525949 + a->month * 43829 + a->day * 1440 + a->hour * 60 + a->minute;
  int b_value = b->year * 525949 + b->month * 43829 + b->day * 1440 + b->hour * 60 + b->minute;

  return a_value - b_value;
}

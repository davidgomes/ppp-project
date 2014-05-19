#include "xtime.h"

int xtime_smaller(xtime *a, xtime *b) // is a smaller than b
{
  if (a->year < b->year)
  {
    return 1;
  }
  else if (a->year > b->year)
  {
    return 0;
  }

  if (a->month < b->month)
  {
    return 1;
  }
  else if (a->month > b->month)
  {
    return 0;
  }

  if (a->day < b->day)
  {
    return 1;
  }
  else if (a->day > b->day)
  {
    return 0;
  }

  if (a->hour < b->hour)
  {
    return 1;
  }
  else if (a->hour > b->hour)
  {
    return 0;
  }

  if (a->minute < b->minute)
  {
    return 1;
  }
  else if (a->minute > b->minute)
  {
    return 0;
  }

  return 0;
}

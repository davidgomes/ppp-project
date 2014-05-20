#ifndef XTIME_HEADER
#define XTIME_HEADER

#include <stdio.h>

typedef struct xtime {
  int year, month, day;
  int hour, minute;
} xtime;

int xtime_smaller(xtime*, xtime*);
int xtime_comp(xtime*, xtime*);

#endif

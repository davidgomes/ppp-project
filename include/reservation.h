#ifndef RESERVATION_HEADER
#define RESERVATION_HEADER

#include <stdlib.h>
#include <time.h>

#include "client.h"

typedef struct reservation
{
  client *owner;
} reservation;

#endif

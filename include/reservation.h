#ifndef RESERVATION_HEADER
#define RESERVATION_HEADER

#include <stdlib.h>
#include <time.h>

#include "client.h"

typedef struct {
  client *owner;
  struct reservation *next;
} reservation;

#endif

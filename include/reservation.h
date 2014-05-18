#ifndef RESERVATION_HEADER
#define RESERVATION_HEADER

#include <stdlib.h>
#include <time.h>

#include "client.h"
#include "llist.h"

typedef struct reservation
{
  client *client;
  time_t register_time;
  time_t actual_time;
} reservation;

reservation *reservation_new();

void reservation_print(reservation*);
void reservation_listing(lnode*);
int reservation_request_listing(llist*);
int reservation_request_new(llist*, llist*);

#endif

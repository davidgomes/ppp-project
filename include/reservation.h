#ifndef RESERVATION_HEADER
#define RESERVATION_HEADER

#include <stdlib.h>
#include <time.h>

#include "client.h"
#include "llist.h"
#include "xtime.h"

/**
 * Lavagem.
 */
#define RESERVATION_TYPE_CLEANING 1

/**
 * Manutenção.
 */
#define RESERVATION_TYPE_CHECKING 2

/**
 * The reservation structure that holds reservations.
 */
typedef struct reservation
{
  client *client;

  int type;

  xtime register_time;
  xtime actual_time;
} reservation;

/**
 * Allocates memory for and returns a new instance of a reservation.
 */
reservation *reservation_new(client*, int);

/**
 * Converts a reservation type as a character to the corresponding integer.
 */
void reservation_type_str_to_int(char*, int*);

/**
 * Prints the information of a given reservation.
 */
void reservation_print(reservation*);

/**
 * Recursive function to list each reservation.
 */
void reservation_listing(lnode*, int);

/**
 * Handles users asking to list all the reservations.
 */
int reservation_request_listing(llist*);

/**
 * Handles users asking to make a new reservation.
 */
int reservation_request_new(llist*, llist*);

/**
 * Handles users asking to cancel a reservation.
 */
int reservation_request_cancel(llist*);

/**
 * Writes reservations to file.
 */
void write_reservations(char*, llist*);

/**
 * Reads reservations from file.
 */
void read_reservation(char*, llist*, llist*);

/**
 * Recursive bubble sort function for reservations.
 */
lnode *_reservation_sort_rec(lnode*, int);

/**
 * Sorts a list of reservations.
 */
void reservation_sort(llist*, int);

#endif

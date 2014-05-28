#ifndef RESERVATION_HEADER
#define RESERVATION_HEADER

#include <stdlib.h>
#include <time.h>

#include "client.h"
#include "llist.h"
#include "xtime.h"
#include "colors.h"

/**
 * Lavagem.
 */
#define RESERVATION_TYPE_CLEANING 1

/**
 * Manutenção.
 */
#define RESERVATION_TYPE_CHECKING 2

/**
 * Duração de qualquer tipo de reservas, em minutos.
 */
#define RESERVATION_DURATION 30

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
int reservation_type_str_to_int(char*, int*);

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

/**
 * Function to check the reservation type input.
 */
int reservation_type_check(int*, char*);

/**
 * Function that checks the input of the order in which the reservations will be displayed.
 */
int reservation_request_check(int*, char*);

/**
 * Returns the duration in minutes of a reservation according to its type in the statement.
 */
int reservation_get_duration_mins(reservation*);

/**
 * Finds out whether a given time collides with any reservation.
 */
reservation *reservation_any_collision(reservation*, llist*);

#endif

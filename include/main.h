#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "client.h"
#include "reservation.h"
#include "llist.h"

llist *client_list;
llist *reservation_list;

/**
 * The main loop that runs the application's core.
 */
void main_loop();

#endif

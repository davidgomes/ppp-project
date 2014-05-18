#include "reservation.h"

reservation *reservation_new(client *client)
{
  reservation *new_reservation = (reservation*) malloc(sizeof(reservation));
  new_reservation->client = client;
  return new_reservation;
}

void reservation_print(reservation *which)
{
  printf("Imprimindo reserva\n");
  printf("Cliente: %s\n", which->client->name);

  char register_time_str[MAX_TIME_CHARS];
  time_to_str(&(which->register_time), register_time_str);
  printf("Registada em: %s\n", register_time_str);

  char actual_time_str[MAX_TIME_CHARS];
  time_to_str(&(which->actual_time), actual_time_str);
  printf("Data marcada: %s\n", actual_time_str);
}

void reservation_listing(lnode *where)
{
  if (where == NULL)
  {
    return;
  }

  reservation_print((reservation*) where->value);

  printf("\n");

  reservation_listing(where->next);
}

int reservation_request_listing(llist *reservation_list)
{
  reservation_listing(reservation_list->root);
  return 1;
}

int reservation_request_new(llist *reservation_list, llist *client_list)
{
  char request_client_name[MAX_NAME_SIZE];

  get_str_input("Insira o nome do cliente: ", request_client_name, MAX_NAME_SIZE);

  client *request_client;
  request_client = client_find_by_name(client_list, request_client_name);

  reservation *request_reservation = reservation_new(request_client);

  /* Get the current date for the registration date */
  time_t current_time = time(NULL);
  time_t_to_xtime(&(request_reservation->register_time), &current_time);
  
  /* Ask for desired date for the reservation */
  ask_date(&(request_reservation->actual_time));

  llist_insert(reservation_list, request_reservation);

  return 1;
}

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
  printf("Registanda em : %s\n", ctime(&(which->register_time)));
}

void reservation_listing(lnode *where)
{
  if (where == NULL)
  {
    return;
  }

  reservation_print((reservation*) where->value);

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
  request_reservation->register_time = time(NULL); //FIXME Ask for time
  llist_insert(reservation_list, request_reservation);

  return 1;
}

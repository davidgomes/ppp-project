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

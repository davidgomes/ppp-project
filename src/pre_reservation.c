#include "pre_reservation.h"


int pre_reservation_request_new(llist *pre_reservation_list, reservation *request)
{
  /* reservation *request is the original reservation */

  llist_insert(pre_reservation_list, request);
  return 0;
}

void write_pre_reservations(char *file, llist *pre_reservation_list)
{
  FILE *fp;
  reservation *aux;
  lnode *where = pre_reservation_list->root;

  if ((fp = fopen(file, "w")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro na abertura do ficheiro.\n");
    return;
  }

  while (where != NULL)
  {
    aux = where->value;

    fprintf(fp, "%s, %d %d %d/%d/%d %d:%d, %d/%d/%d %d:%d\n", aux->client->name,
            aux->type,
            aux->reservation_type,
            aux->register_time.day,
            aux->register_time.month,
            aux->register_time.year,
            aux->register_time.hour,
            aux->register_time.minute,
            aux->actual_time.day,
            aux->actual_time.month,
            aux->actual_time.year,
            aux->actual_time.hour,
            aux->actual_time.minute);

    where = where->next;
  }

  fclose(fp);
}

void read_pre_reservation(char *file, llist *client_list, llist *pre_reservation_list)
{
  FILE *fp;
  reservation *pre_reservation;
  client *client;
  char client_name[MAX_NAME_SIZE];

  if ((fp = fopen(file, "r")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro.");
    return;
  }

  while (fscanf(fp, "%[^,],", client_name) == 1)
  {
    client = client_find_by_name(client_list, client_name);
    pre_reservation = reservation_new(client, 1);

    fscanf(fp, "%d  %d %d/%d/%d %d:%d, %d/%d/%d %d:%d\n",
           &(pre_reservation->type),
           &(pre_reservation->reservation_type),
           &(pre_reservation->register_time.day),
           &(pre_reservation->register_time.month),
           &(pre_reservation->register_time.year),
           &(pre_reservation->register_time.hour),
           &(pre_reservation->register_time.minute),
           &(pre_reservation->actual_time.day),
           &(pre_reservation->actual_time.month),
           &(pre_reservation->actual_time.year),
           &(pre_reservation->actual_time.hour),
           &(pre_reservation->actual_time.minute));

    llist_insert(pre_reservation_list, pre_reservation);
  }

  fclose(fp);
}

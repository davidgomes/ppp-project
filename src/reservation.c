#include "reservation.h"

reservation *reservation_new(client *client)
{
  reservation *new_reservation = (reservation*) malloc(sizeof(reservation));
  new_reservation->client = client;
  return new_reservation;
}

void reservation_print(reservation *which)
{
  printf("Cliente: %s\n", which->client->name);

  char register_time_str[MAX_TIME_CHARS];
  time_to_str(&(which->register_time), register_time_str);
  printf("Registada em: %s\n", register_time_str);

  char actual_time_str[MAX_TIME_CHARS];
  time_to_str(&(which->actual_time), actual_time_str);
  printf("Data marcada: %s\n", actual_time_str);
}

void reservation_listing(lnode *where, int index)
{
  if (where == NULL)
  {
    return;
  }

  printf("Listando reserva número %d\n", index);
  reservation_print((reservation*) where->value);

  printf("\n");

  reservation_listing(where->next, index + 1);
}

int reservation_request_listing(llist *reservation_list)
{
  char which_order_str[5];
  get_str_input("Deseja ordenar por mais recentes [R] ou mais antigas [A]?: ", which_order_str, 5);

  if (strcmp(which_order_str, "R") == 0)
  {
    reservation_sort(reservation_list, 1);
  }
  else if (strcmp(which_order_str, "A") == 0)
  {
    reservation_sort(reservation_list, 0);
  }

  reservation_listing(reservation_list->root, 1);
  return 1;
}

int reservation_request_new(llist *reservation_list, llist *client_list)
{
  char request_client_name[MAX_NAME_SIZE];
  get_str_input("Insira o nome do cliente: ", request_client_name, MAX_NAME_SIZE);

  client *request_client;
  request_client = client_find_by_name(client_list, request_client_name);

  if (request_client == NULL)
  {
    request_client = client_new(request_client_name);
    llist_insert(client_list, request_client);
  }

  reservation *request_reservation = reservation_new(request_client);

  /* Get the current date for the registration date */
  time_t current_time = time(NULL);
  time_t_to_xtime(&(request_reservation->register_time), &current_time);

  /* Ask for desired date for the reservation */
  ask_date(&(request_reservation->actual_time));

  if (xtime_comp(&(request_reservation->actual_time), &(request_reservation->register_time)) < 0)
  {
    printf("Não pode reservar para o passado.\n");
    return 0;
  }

  llist_insert(reservation_list, request_reservation);

  printf("%p\n", request_client);

  return 1;
}

int reservation_request_cancel(llist *reservation_list)
{
  printf("Listando todas as reservas.\n\n");

  reservation_request_listing(reservation_list);

  int which_reservation;
  get_int_input("Insira o número da reserva que deseja cancelar: ",
                &which_reservation);

  if (which_reservation > llist_get_size(reservation_list) ||
      which_reservation < 1)
  {
    printf("Não existe um item correspondente ao número que escolheu.\n");
    return 0;
  }

  llist_remove_by_index(reservation_list, which_reservation - 1);

  return 1;
}

void write_reservations(char *file, lnode *where)
{
  FILE *fp;
  reservation *aux;

  if ((fp = fopen(file, "w")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro na abertura do ficheiro");
    return;
  }

  while (where != NULL)
  {
    aux = where->value;

    fprintf(fp, "%s, %d/%d/%d %d:%d, %d/%d/%d %d:%d\n", aux->client->name,
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

void read_reservation(char *file, llist *client_list, llist *reservation_list)
{
  FILE *fp;
  reservation *reservation;
  client *client;
  char client_name[MAX_NAME_SIZE];

  if ((fp = fopen(file, "r")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro");
    return;
  }

  while (fscanf(fp, "%[^,],", client_name) == 1)
  {
    client = client_find_by_name(client_list, client_name);
    reservation = reservation_new(client);

    fscanf(fp, "%d/%d/%d %d:%d, %d/%d/%d %d:%d\n",
           &(reservation->register_time.day),
           &(reservation->register_time.month),
           &(reservation->register_time.year),
           &(reservation->register_time.hour),
           &(reservation->register_time.minute),
           &(reservation->actual_time.day),
           &(reservation->actual_time.month),
           &(reservation->actual_time.year),
           &(reservation->actual_time.hour),
           &(reservation->actual_time.minute));

    llist_insert(reservation_list, reservation);
  }

  fclose(fp);
}

lnode *_reservation_sort_rec(lnode *start, int order)
{
  if (start == NULL)
  {
    return NULL;
  }

  // FIXME This code is awful

  if (order)
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) > 0)
    {
      start = _llist_swap(start, start->next);
    }
  }
  else
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) < 0)
    {
      start = _llist_swap(start, start->next );
    }
  }

  start->next = _reservation_sort_rec(start->next, order);

  if (order)
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) > 0)
    {
      start = _llist_swap(start, start->next);
      start->next = _reservation_sort_rec(start->next, order);
    }
  }
  else
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) < 0)
    {
      start = _llist_swap(start, start->next);
      start->next = _reservation_sort_rec(start->next, order);
    }
  }

  return start;
}

void reservation_sort(llist *reservation_list, int order)
{
  reservation_list->root = _reservation_sort_rec(reservation_list->root, order);
}

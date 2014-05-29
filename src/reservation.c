#include "reservation.h"

reservation *reservation_new(client *client, int type)
{
  reservation *new_reservation = (reservation*) malloc(sizeof(reservation));
  new_reservation->client = client;
  new_reservation->type = type;
  return new_reservation;
}

int reservation_type_str_to_int(char *str, int *integer)
{
  if (!strcmp(str, "L"))
  {
    *integer = RESERVATION_TYPE_CLEANING;
    return 0;
  }
  else if (!strcmp(str, "M"))
  {
    *integer = RESERVATION_TYPE_CHECKING;
    return 0;
  }
  else
  {
    return 1;
  }
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

  printf("Trata-se de uma ");
  if (which->type == RESERVATION_TYPE_CLEANING)
  {
    printf("lavagem.\n");
  }
  else if (which->type == RESERVATION_TYPE_CHECKING)
  {
    printf("manutenção.\n");
  }
  else
  {
    printf("ERRO.\n");
  }
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
  char which_order_str[MAX_CHAR];
  int reservation_sort_order = -1;

  do
  {
    get_str_input("Deseja ordenar por mais recentes [R] ou mais antigas [A]?: ",
                  which_order_str, MAX_CHAR);

  } while (reservation_request_check(&reservation_sort_order, which_order_str));

  reservation_sort(reservation_list, reservation_sort_order);

  reservation_listing(reservation_list->root, 1);
  return 1;
}

int reservation_request_new(llist *reservation_list, llist *client_list, llist *pre_reservation_list)
{
  char request_client_name[MAX_NAME_SIZE];
  while (get_str_input("Insira o nome do cliente: ", request_client_name, MAX_NAME_SIZE))
  {
    printf("Input incorreto.\n");
  }

  client *request_client;
  request_client = client_find_by_name(client_list, request_client_name);

  if (request_client == NULL)
  {
    request_client = client_new(request_client_name);
    llist_insert(client_list, request_client);
  }

  /* Asks the user for what type of a reservation it is. */
  int request_reservation_type = -1;
  char request_reservation_type_str[MAX_CHAR];

  do
  {
    get_str_input("Que tipo de serviço deseja, lavagem [L] ou manutenção [M]: ",
                  request_reservation_type_str, MAX_CHAR);

  } while (reservation_type_check(&request_reservation_type,
                                  request_reservation_type_str));

  reservation *request_reservation = reservation_new(request_client, request_reservation_type);

  /* Get the current date for the registration date */
  time_t current_time = time(NULL);
  time_t_to_xtime(&(request_reservation->register_time), &current_time);

  /* Ask for desired date for the reservation */
  while (ask_date(&(request_reservation->actual_time)) || xtime_validate(&(request_reservation->actual_time)))
  {
    printf("Por favor introduza uma data correta.\n");
  }

  if (xtime_comp(&(request_reservation->actual_time), &(request_reservation->register_time)) < 0)
  {
    printf("Não pode reservar para o passado.\n");
    return 1;
  }

  reservation *find_collision = reservation_any_collision(request_reservation, reservation_list);

  if (find_collision)
  {
    char collision_date[MAX_TIME_CHARS];
    time_to_str(&(find_collision->actual_time), collision_date);
    printf("Foi encontrada uma reserva que colide com a sua a começar às: %s\n", collision_date);

    do
    {
      char pre_reservation_decision_str[MAX_CHAR];
      get_str_input("Deseja [G]uardar a sua reserva na lista de pré-reservas ou [M]udar a data para outra que também lhe convenha: ",
                    pre_reservation_decision_str, MAX_CHAR);

      // TODO Actually do shit about G/M, for now just always pre-reserve.
      pre_reservation_request_new(pre_reservation_list, request_reservation);
    } while (0);

    return 0;
  }

  llist_insert(reservation_list, request_reservation);

  printf("%p\n", request_client);

  return 0;
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

void write_reservations(char *file, llist *reservation_list)
{
  FILE *fp;
  reservation *aux;
  lnode *where = reservation_list->root;

  if ((fp = fopen(file, "w")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro na abertura do ficheiro.\n");
    return;
  }

  while (where != NULL)
  {
    aux = where->value;

    fprintf(fp, "%s, %d %d/%d/%d %d:%d, %d/%d/%d %d:%d\n", aux->client->name,
            aux->type,
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
    fprintf(stderr, "Ocorreu um erro.");
    return;
  }

  while (fscanf(fp, "%[^,],", client_name) == 1)
  {
    client = client_find_by_name(client_list, client_name);
    reservation = reservation_new(client, 1);

    fscanf(fp, "%d %d/%d/%d %d:%d, %d/%d/%d %d:%d\n",
           &(reservation->type),
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

int reservation_type_check(int *request_reservation_type, char *request_reservation_type_str)
{
  if (strlen(request_reservation_type_str) != SINGLE_INPUT_SIZE)
  {
    printf("O input nao tem o tamanho correto.\n");
    return 1;
  }

  if (check_if_lower(request_reservation_type_str))
  {
    char_to_upper(request_reservation_type_str);
  }

  if (reservation_type_str_to_int(request_reservation_type_str,
                                  request_reservation_type))
  {
    printf("O input é incorreto.\n");
    return 1;
  }

  return 0;
}

int reservation_request_check(int *reservation_sort_order, char *which_order_str)
{
  if (strlen(which_order_str) != SINGLE_INPUT_SIZE)
  {
    printf("O input nao tem o tamanho correto.\n");
    return 1;
  }

  if (check_if_lower(which_order_str))
  {
    char_to_upper(which_order_str);
  }

  if (!strcmp(which_order_str, "R"))
  {
    *reservation_sort_order = 1;
    return 0;
  }
  else if (!strcmp(which_order_str, "A"))
  {
    *reservation_sort_order = 0;
    return 0;
  }
  else
  {
    printf("O input é incorreto.\n");
    return 1;
  }

  return 0;
}

void reservation_remove_outdated(llist *reservation_list)
{
  time_t current_time = time(NULL);
  xtime current_xtime;
  lnode *start = reservation_list->root;

  time_t_to_xtime(&current_xtime, &current_time);

  while (start != NULL)
  {
    if (xtime_comp(&(((reservation*) start->value)->actual_time), &current_xtime) < 0)
    {
      llist_remove(reservation_list, start->value); 
    }

    start = start->next;
  }
}

int reservation_get_duration_mins(reservation *which)
{
  if (which->type == RESERVATION_TYPE_CLEANING)
  {
    return 30; // Cleanings take 30 minutes...
  }
  else
  {
    return 60; // ... but checkings take 60 minutes.
  }
}

reservation *reservation_any_collision(reservation *which, llist *reservation_list)
{
  lnode *current_node = reservation_list->root;

  xtime start_of_which = which->actual_time;
  xtime end_of_which = start_of_which;
  end_of_which.minute += reservation_get_duration_mins(which);

  while (current_node != NULL)
  {
    reservation *current = (reservation*) current_node->value;

    xtime start_of_current = current->actual_time;
    xtime end_of_current = start_of_current;
    end_of_current.minute += reservation_get_duration_mins(current);

    /* Check if "which" starts during current */

    if (xtime_comp(&start_of_which, &start_of_current) >= 0 &&
        xtime_comp(&start_of_which, &end_of_current) <= 0)
    {
      return current;
    }

    /* Check if "which" ends during current */

    if (xtime_comp(&end_of_which, &start_of_current) >= 0 &&
        xtime_comp(&end_of_which, &end_of_current) <= 0)
    {
      return current;
    }

    current_node = current_node->next;
  }

  return NULL;
}

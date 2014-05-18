#include "client.h"

client *client_new(char *name)
{
  client *new_client = (client*) malloc(sizeof(client));
  strcpy(new_client->name, name);
  return new_client;
}

client *_client_find_by_name_rec(lnode *where, char *find_name)
{
  if (where == NULL)
  {
    return NULL;
  }

  if (strcmp(((client*) where->value)->name, find_name) == 0)
  {
    return (client*) where->value;
  }

  return _client_find_by_name_rec(where->next, find_name);
}

client *client_find_by_name(llist *client_list, char *find_name)
{
  return _client_find_by_name_rec(client_list->root, find_name);
}

int client_request_print(llist *client_list)
{
  char request_str[] = "Insira o nome do cliente: ";
  char client_name[MAX_NAME_SIZE];
  get_str_input(request_str, client_name, MAX_NAME_SIZE);

  client *found_client = client_find_by_name(client_list, client_name);

  if (found_client == NULL)
  {
    return 0;
  }
  else
  {
    return client_print(found_client);
  }
}

int client_print(client *which)
{
  if (which == NULL)
  {
    printf("Client não encontrado em client_print.\n");
    return 0;
  }

  printf("Printing information on %s\n", which->name);
  printf("%d\n", which->id);

  return 1;
}

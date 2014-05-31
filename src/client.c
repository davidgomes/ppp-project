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
  
  if (get_str_input(request_str, client_name, MAX_NAME_SIZE) == 2)
  {
    return 2;
  }

  client *found_client = client_find_by_name(client_list, client_name);

  if (found_client == NULL)
  {
    printf("Cliente não encontrado, verifique o nome introduzido.\n");
    return 1;
  }
  else
  {
    return client_print(found_client);
  }
  return 0;
}

int client_print(client *which)
{
  if (which == NULL)
  {
    printf("Client não encontrado em client_print.\n");
    return 1;
  }

  printf("Printing information on %s\n", which->name);
  printf("%d\n", which->id);

  return 0;
}

void write_client(char *file, llist *client_list)
{
  FILE *fp;
  client *node_value;
  lnode *where = client_list->root;

  if ((fp = fopen(file, "w")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro na abertura do ficheiro");
    return;
  }

  while (where != NULL)
  {
    node_value = where->value;
    fprintf(fp, "%s, %d\n",node_value->name, node_value->id);
    where = where->next;
  }

  fclose(fp);
}

void read_client(char *file, llist *client_list)
{
  FILE *fp;
  char client_name[MAX_NAME_SIZE];
  int client_id;
  client *client;

  if ((fp = fopen(file, "r")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro");
    return ;
  }

  while (fscanf(fp, "%[^,], %d\n", client_name, &client_id) == 2)
  {
    client = client_new(client_name);
    client->id = client_id;
    llist_insert(client_list, client);
  }

  fclose(fp);
}

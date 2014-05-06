#include "client.h"

client *client_create(char *name)
{
  client *new_client = (client*) malloc(sizeof(client));
  strcpy(new_client->name, name);
  return new_client;
}

void client_request_print()
{
  char request_str[] = "Insira o nome do cliente: ";
  char client_name[MAX_NAME_SIZE];
  get_input(request_str, client_name, MAX_NAME_SIZE);
}

void client_print(client *which)
{
  printf("Printing information on %s\n", which->name);
  printf("%d\n", which->id);
}

#include "client.h"

client *client_create()
{
  client *new_client = (client*) malloc(sizeof(client));
  return new_client;
}

void client_print(client *which)
{
  printf("Printing information on %s\n", which->name);
  printf("%d\n", which->id);
}

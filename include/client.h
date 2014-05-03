#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[200];
  int id;

  struct client *next;
} client;

client *client_create();
void client_print();

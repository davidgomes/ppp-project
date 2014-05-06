#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "llist.h"

#define MAX_NAME_SIZE 128

typedef struct client
{
  char name[MAX_NAME_SIZE];
  int id;
} client;

client *client_create(char*);

client *_client_find_by_name_rec(lnode*, char*);
client *client_find_by_name(llist*, char*);

void client_request_print(llist*);
void client_print();

#endif

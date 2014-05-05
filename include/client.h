#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define MAX_NAME_SIZE 128

typedef struct
{
  char name[MAX_NAME_SIZE];
  int id;

  struct client *next;
} client;

client *client_create();
void client_request_print();
void client_print();

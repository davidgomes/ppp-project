#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_NAME_SIZE 128

typedef struct client
{
  char name[MAX_NAME_SIZE];
  int id;
} client;

client *client_create(char*);

void client_request_print();
void client_print();

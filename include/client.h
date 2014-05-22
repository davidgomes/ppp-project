#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "llist.h"

#define MAX_NAME_SIZE 128

/**
 * The client structure.
 */
typedef struct client
{
  char name[MAX_NAME_SIZE];
  int id;
} client;

/**
 * Allocates memory for and returns a new client.
 */
client *client_new(char*);

/**
 * Recursive function to find a client by name.
 */
client *_client_find_by_name_rec(lnode*, char*);

/**
 * Finds a client by its name.
 */
client *client_find_by_name(llist*, char*);

/**
 * Handles user asking to print a client.
 */
int client_request_print(llist*);

/**
 * Prints the information on a given client.
 */
int client_print(client*);

/**
 * Write all clients to a file.
 */
void write_client(char*, lnode*);

/**
 * Reads all clients from a file.
 */
void read_client(char*, llist*);

#endif

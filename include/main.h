#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "client.h"
#include "llist.h"

llist *client_list;
llist *reservation_list;

void main_loop();

client *find_client_by_name();

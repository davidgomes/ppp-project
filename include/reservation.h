#include <stdlib.h>
#include <time.h>

#include "client.h"

typedef struct {
  client *owner;
  struct reservation *next;
} reservation;

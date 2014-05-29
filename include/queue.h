#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <stdlib.h>

/**
 * The abstract item for queues, qitem, values are pointed ot in ->value.
 */
typedef struct qitem
{
  void *value;
  struct qitem *next;
  struct qitem *previous;
} qitem;

/**
 * The queue structure.
 */
typedef struct queue
{
  qitem *front;
  qitem *rear;
} queue;

/**
 * Allocates memory for and returns a new queue.
 */
queue *queue_new();

/**
 * Allocates memory for and returns a new qitem from a given void* value.
 */
qitem *item_new(void*);

/**
 * Pushes a new element into a given queue.
 */
void queue_push(queue*, void*);

/**
 * Tests whether a given queue is empty.
 */
int queue_is_empty(queue*);

#endif

#include "queue.h"

queue *queue_new()
{
  queue *new_queue = (queue*) malloc(sizeof(queue));

  new_queue->front = NULL;
  new_queue->rear = NULL;

  return new_queue;
}

qitem *qitem_new(void *value)
{
  qitem *new_item = (qitem*) malloc(sizeof(qitem));
  new_item->value = value;
  new_item->next = NULL;
  return new_item;
}

void queue_push(queue *which, void *value)
{
  qitem *new_item = qitem_new(value);

  if (queue_is_empty(which))
  {
    which->front = new_item;
    new_item->previous = NULL;
  }
  else
  {
    which->rear->next = new_item;
    new_item->previous = which->rear;
  }

  which->rear = new_item;
}

int queue_is_empty(queue *which)
{
  return which->front == NULL;
}

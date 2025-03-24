#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

enum QUEUE_STATUS_ENUM {
  QUEUE_OK_ENQUEUED_ELEMENT,
  QUEUE_ERROR_CANNOT_ENQUEUE_ELEMENT,
  QUEUE_OK_DEQUEUED_ELEMENT,
  QUEUE_ERROR_DEQUEUE_ELEMENT,
  QUEUE_ERROR_CANNOT_DEQUEUE_ELEMENT_EMPTY_LIST,
  QUEUE_ERROR_NODES_ARE_NOT_ADJ,
};

typedef struct {
  node *n;
  enum QUEUE_STATUS_ENUM status;
} queue_status;

typedef struct __queue {
  list *l;
} queue;

queue *queue_new(int (*)(const void *, const void *));
bool queue_is_empty(queue *);
size_t queue_size(queue *);
queue_status enqueue(queue *, const void *);
queue_status dequeue(queue *);

#endif // !DEBUG

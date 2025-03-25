#include "queue.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

queue *queue_new(int (*compare)(const void *, const void *)) {
  queue *qq = (queue *)calloc(1, sizeof(queue));
  qq = list_new(compare);
  return qq;
}

bool queue_is_empty(queue *q) { return list_is_empty(q); }

size_t queue_size(queue *q) { return q->length; }

queue_status enqueue(queue *q, const void *value) {
  list_status ls = list_add_last(q, (const void *)value);

  switch (ls.status) {
  case LIST_OK_ADDED_ELEMENT:
    return (queue_status){.n = NULL, .status = QUEUE_OK_ENQUEUED_ELEMENT};
  case LIST_ERROR_NODES_ARE_NOT_ADJACENTS:
    return (queue_status){.n = NULL, .status = QUEUE_ERROR_NODES_ARE_NOT_ADJ};
  default:
    return (queue_status){.n = NULL,
                          .status = QUEUE_ERROR_CANNOT_ENQUEUE_ELEMENT};
  }
}

queue_status dequeue(queue *q) {
  list_status ls = list_remove_first(q);
  switch (ls.status) {
  case LIST_EMPTY_LIST:
    return (queue_status){
        .n = NULL, .status = QUEUE_ERROR_CANNOT_DEQUEUE_ELEMENT_EMPTY_LIST};
  case LIST_OK_REMOVED_ELEMENT:
    return (queue_status){.n = ls.n, .status = QUEUE_OK_DEQUEUED_ELEMENT};
  default:
    return (queue_status){.n = NULL, .status = QUEUE_ERROR_DEQUEUE_ELEMENT};
  }
}


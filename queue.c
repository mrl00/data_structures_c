#include "queue.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

queue *queue_new(int (*compare)(const void *, const void *)) {
  queue *qq = (queue *)calloc(1, sizeof(queue));
  qq->l = list_new(compare);
  return qq;
}

bool queue_is_empty(queue *q) { return list_is_empty(q->l); }

size_t queue_size(queue *q) { return q->l->length; }

queue_status enqueue(queue *q, const void *value) {
  list_status ls = list_add_last(q->l, (const void *)value);

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
  list_status ls = list_remove_first(q->l);
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

int q_compare_int(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}
/*
int main(void) {
  queue *qq = queue_new(q_compare_int);

  int xs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (size_t i = 0; i <= 9; i++)
    enqueue(qq, &xs[i]);

  for (node *i = qq->l->header->next; i->next != NULL; i = i->next)
    printf("%d ", *(int *)i->value);
  printf("\n");

  for (size_t i = 0; i <= 5; i++)
    dequeue(qq);

  for (node *i = qq->l->header->next; i->next != NULL; i = i->next)
    if (!queue_is_empty(qq))
      printf("%d ", *(int *)i->value);
  printf("\n");

  return EXIT_SUCCESS;
}
*/

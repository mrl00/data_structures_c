#include "queue.h"
#include <stdio.h>

int q_compare_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main(void) {
    queue *qq = queue_new(q_compare_int);
  
    int xs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
    for (size_t i = 0; i <= 9; i++)
      enqueue(qq, &xs[i]);
  
    for (node *i = qq->header->next; i->next != NULL; i = i->next)
      printf("%d ", *(int *)i->value);
    printf("\n");
  
    for (size_t i = 0; i <= 5; i++)
      dequeue(qq);
  
    for (node *i = qq->header->next; i->next != NULL; i = i->next)
      if (!queue_is_empty(qq))
        printf("%d ", *(int *)i->value);
    printf("\n");
  
    return EXIT_SUCCESS;
}

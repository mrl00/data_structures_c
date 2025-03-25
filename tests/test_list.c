#include "list.h"
#include <stdio.h>

int cmp_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main(void) {
    list *ll = list_new(cmp_int);
    int xs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  
    for (size_t i = 0; i <= 4; i++)
      list_add_first(ll, &xs[i]);
  
    for (size_t i = 5; i <= 9; i++)
      list_add_last(ll, &xs[i]);
  
    for (node *i = ll->header->next; i->next != NULL; i = i->next)
      printf("%d ", *(int *)i->value);
    printf("\n");
  
    list_remove(ll, &xs[9]);
    list_remove(ll, &xs[0]);
    list_remove(ll, &xs[3]);
  
    for (node *i = ll->header->next; i->next != NULL; i = i->next)
      printf("%d ", *(int *)i->value);
    printf("\n");
  
    list_remove_first(ll);
    list_remove_first(ll);
    list_remove_first(ll);
  
    for (node *i = ll->header->next; i->next != NULL; i = i->next)
      printf("%d ", *(int *)i->value);
    printf("\n");
  
    list_remove_last(ll);
    list_remove_last(ll);
    list_remove_last(ll);
  
    for (node *i = ll->header->next; i->next != NULL; i = i->next)
      printf("%d ", *(int *)i->value);
    printf("\n");
  
    return EXIT_SUCCESS;
  }
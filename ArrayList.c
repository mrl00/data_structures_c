#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  void**  values;
  size_t  len, capacity;
  void*   minimum;
  void*   maximum;
  int     (*compare)(const void*, const void*);
} ArrList;

ArrList* init_list(size_t capacity, int (*compare)(const void*, const void*)) {
  ArrList *l = (ArrList*) calloc(1, sizeof(ArrList));
  l->capacity = capacity;
  l->len = 0;
  l->values = (void**) calloc(capacity, sizeof(void*));
  l->compare = compare;
  l->minimum = l->maximum = NULL;
  return l;
}

void add_value(ArrList *l, void *value) {
  if(l->len == l->capacity) {
    l->capacity += 100;
    l->values = realloc(l->values, l->capacity *sizeof(void*));
  }
  
  if(l->minimum == NULL || l->compare(l->minimum, value) > 0)
    l->minimum = value;
  if(l->maximum == NULL || l->compare(l->maximum, value) < 0)
    l->maximum = value;

  l->values[l->len++] = value;
}

void destroy_arrlist(ArrList *list, void (*destroy_value)(void* value)) {
  for(int i = 0; i < list->len; i++)
    destroy_value(*(list->values + i));
  free(list);
}

bool is_empty(ArrList *list) { return list->len == 0;}

int main(void) {
 return  EXIT_SUCCESS;
}

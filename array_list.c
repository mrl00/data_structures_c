#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** START LIST **/
typedef struct {
  void**  values;
  size_t  len, capacity;
  void*   minimum;
  void*   maximum;
  int     (*compare)(const void*, const void*);
} array_list;

array_list* init_list(size_t capacity, int (*compare)(const void*, const void*)) {
  array_list *l = (array_list*) calloc(1, sizeof(array_list));
  l->capacity = capacity;
  l->len = 0;
  l->values = (void**) calloc(capacity + 1, sizeof(void*)); 
  l->values[capacity] = NULL;
  l->compare = compare;
  l->minimum = l->maximum = NULL;
  return l;
}

void add_value(array_list *l, void *value) {
  if(l->len == l->capacity) {
    l->capacity += 100;
    l->values = realloc(l->values, l->capacity *sizeof(void*));
  }
  
  if(l->minimum == NULL || l->compare(l->minimum, value) < 0)
    l->minimum = value;
  if(l->maximum == NULL || l->compare(l->maximum, value) > 0)
    l->maximum = value;

  l->values[l->len++] = value;
}

void destroy_arrlist(array_list *list, void (*destroy_value)(void* value)) {
  for(int i = 0; i < list->len; i++)
    destroy_value(*(list->values + i));
  free(list);
}

void walk(array_list *l, void (*action)(void*)) {
  for(void** i = l->values; *i != NULL; ++i)
    action((*i));
}

bool is_empty(array_list *list) { return list->len == 0;}
/** END LIST **/

typedef struct {
  int a;
} a_test;

int compare_test(const void* a, const void* b) {
  a_test *x = (a_test*) a;
  a_test *y = (a_test*) b;
  return (y->a - x->a);
}

int compare_int(const void* a, const void* b) {
  return (*(int*)b - *(int*)a);
}

void show_test(void *t) {
  printf("%d ", ((a_test*) t)->a);
}

void show_int(void* i) {
  printf("%d ", *(int*)i);
}


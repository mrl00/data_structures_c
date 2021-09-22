#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
  l->values = (void**) calloc(capacity + 1, sizeof(void*)); 
  l->values[capacity] = NULL;
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

void walk(ArrList *l, void (*action)(void*)) {
  for(void** i = l->values; *i != NULL; ++i)
    action((*i));
}

bool is_empty(ArrList *list) { return list->len == 0;}

typedef struct {
  int a;
} Test;

int compare_test(const void* a, const void* b) {
  Test *x = (Test*) a;
  Test *y = (Test*) b;
  return (y->a - x->a);
}

void show_test(void *t) {
  printf("t-value::%d\n", ((Test*) t)->a);
}

int main(void) {
  Test t[] = {{.a = 3}, {.a = 2}, {.a = 1}};

  ArrList *l = init_list(3, compare_test);
  add_value(l, &t);
  add_value(l, &t[1]);
  add_value(l, &t[2]);

  qsort(l->values, l->len, sizeof(void*), compare_test);

  walk(l, show_test);

  return  EXIT_SUCCESS;
}

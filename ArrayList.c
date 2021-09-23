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
  
  if(l->minimum == NULL || l->compare(l->minimum, value) < 0)
    l->minimum = value;
  if(l->maximum == NULL || l->compare(l->maximum, value) > 0)
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
/** END LIST **/

typedef struct {
  int a;
} Test;

int compare_test(const void* a, const void* b) {
  Test *x = (Test*) a;
  Test *y = (Test*) b;
  return (y->a - x->a);
}

int compare_int(const void* a, const void* b) {
  return (*(int*)b - *(int*)a);
}

void show_test(void *t) {
  printf("%d ", ((Test*) t)->a);
}

void show_int(void* i) {
  printf("%d ", *(int*)i);
}

int main(void) {
  // Struct Test
  Test t[] = {{.a = 3}, {.a = 2}, {.a = 1}};
  ArrList *t_list = init_list(3, compare_test);
  add_value(t_list, &t);
  add_value(t_list, &t[1]);
  add_value(t_list, &t[2]);

  printf("before qsort: "); walk(t_list, show_test);
  qsort(t_list->values, t_list->len, sizeof(void*), t_list->compare);
  printf("\nafter qsort: "); walk(t_list, show_test);
  printf("\nminimum: %d\n",((Test*) t_list->minimum)->a);
  printf("maximum: %d\n",((Test*) t_list->maximum)->a);

  // Int test
  int i[] = {5,4,3,2,1};
  ArrList *i_list = init_list(5, compare_int);
  add_value(i_list, &i);
  add_value(i_list, &i[1]);
  add_value(i_list, &i[2]);
  add_value(i_list, &i[3]);
  add_value(i_list, &i[4]);
  
  printf("\nbefore qsort: "); walk(i_list, show_int);
  qsort(i_list->values, i_list->len, sizeof(void*), i_list->compare);
  printf("\nafter qsort: "); walk(i_list, show_int);
  printf("\nminimum: %d\n",((Test*) i_list->minimum)->a);
  printf("maximum: %d\n",((Test*) i_list->maximum)->a);

  return  EXIT_SUCCESS;
}

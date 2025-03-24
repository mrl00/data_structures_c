#include "list.h"
#include <stdio.h>

node *node_new(node *prev, node *next, const void *value) {
  node *n = (node *)calloc(1, sizeof(node));
  n->value = (void *)value;
  n->prev = prev, n->next = next;
  return n;
}

list *list_new(int (*compare)(const void *, const void *)) {
  list *l = (list *)calloc(1, sizeof(list));

  l->compare = compare;
  l->length = 0;

  l->header = node_new(NULL, NULL, NULL);
  l->trailer = node_new(NULL, NULL, NULL);

  l->header->next = l->trailer;
  l->trailer->prev = l->header;
  return l;
}

bool list_is_empty(list *l) { return l->length == 0; }

node *list_find(list *l, const void *value) {
  for (node *i = l->header->next; i->next != NULL; i = i->next)
    if (l->compare(i->value, value) == 0)
      return i;
  return NULL;
}

list_status list_add_node_between(node *a, node *b, const void *value) {
  if (a->next != b || b->prev != a)
    return (list_status){.n = NULL,
                         .status = LIST_ERROR_NODES_ARE_NOT_ADJACENTS};

  node *n = node_new(a, b, value);

  a->next = n, b->prev = n;

  return (list_status){.n = n, .status = LIST_OK_ADDED_ELEMENT};
}

list_status list_first(list *l) {
  if (list_is_empty(l))
    return (list_status){.n = NULL, .status = LIST_EMPTY_LIST};
  return (list_status){.n = l->header->next, .status = LIST_FIRST_NODE};
}

list_status list_last(list *l) {
  if (list_is_empty(l))
    return (list_status){.n = NULL, .status = LIST_EMPTY_LIST};
  return (list_status){.n = l->trailer->prev, .status = LIST_LAST_NODE};
}

list_status list_add_first(list *l, const void *value) {
  list_status ls = list_add_node_between(l->header, l->header->next, value);
  if (ls.status == LIST_OK_ADDED_ELEMENT)
    l->length++;
  return ls;
}

list_status list_add_last(list *l, const void *value) {
  list_status ls = list_add_node_between(l->trailer->prev, l->trailer, value);
  if (ls.status == LIST_OK_ADDED_ELEMENT)
    l->length++;
  return ls;
}

list_status list_remove_first(list *l) {
  if (list_is_empty(l))
    return (list_status){.n = NULL, .status = LIST_EMPTY_LIST};

  node *first_node = l->header->next;

  first_node->next->prev = first_node->prev;
  first_node->prev->next = first_node->next;
  first_node->prev = first_node->next = NULL;

  l->length--;

  return (list_status){.n = first_node, .status = LIST_OK_REMOVED_ELEMENT};
}

list_status list_remove_last(list *l) {
  if (list_is_empty(l))
    return (list_status){.n = NULL, .status = LIST_EMPTY_LIST};

  node *last_node = l->trailer->prev;

  last_node->next->prev = last_node->prev;
  last_node->prev->next = last_node->next;
  last_node->prev = last_node->next = NULL;

  l->length--;

  return (list_status){.n = last_node, .status = LIST_OK_REMOVED_ELEMENT};
}

list_status list_remove(list *l, const void *value) {
  node *found_node = list_find(l, value);
  if (found_node == NULL)
    return (list_status){.n = NULL,
                         .status = LIST_ERROR_CANNOT_REMOVE_ELEMENT_NOT_FOUND};

  found_node->next->prev = found_node->prev;
  found_node->prev->next = found_node->next;

  found_node->next = found_node->prev = NULL;

  return (list_status){.n = found_node, .status = LIST_OK_REMOVED_ELEMENT};
}

int l_compare_int(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}
/**
int main(void) {
  list *ll = list_new(compare_int);
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
*/

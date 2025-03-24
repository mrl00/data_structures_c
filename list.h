#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stdlib.h>

enum LIST_STATUS_ENUM {
  LIST_OK_ADDED_ELEMENT,
  LIST_ERROR_CANNOT_ADD_ELEMENT,
  LIST_ERROR_NODES_ARE_NOT_ADJACENTS,
  LIST_OK_REMOVED_ELEMENT,
  LIST_ERROR_CANNOT_REMOVE_ELEMENT_NOT_FOUND,
  LIST_EMPTY_LIST,
  LIST_FIRST_NODE,
  LIST_LAST_NODE
};

typedef struct __node {
  void *value;
  struct __node *prev, *next;
} node;

node *node_new(node *prev, node *next, const void *value);

typedef struct {
  node *n;
  enum LIST_STATUS_ENUM status;
} list_status;

typedef struct __list {
  node *header, *trailer;
  size_t length;
  int (*compare)(const void *, const void *);
} list;

list *list_new(int (*compare)(const void *, const void *));
node *list_find(list *l, const void *x);
bool list_is_empty(list *);

list_status list_add_node_between(node *a, node *b, const void *value);
list_status list_first(list *l);
list_status list_last(list *l);
list_status list_add_first(list *l, const void *value);
list_status list_add_last(list *l, const void *value);
list_status list_remove_first(list *l);
list_status list_remove_last(list *l);
list_status list_remove(list *l, const void *value);

#endif // !__LIST_H__

#include "set.h"
#include "list.h"
#include <stdio.h>

const char *set_status_string(enum SET_STATUS_ENUM code) {
  switch (code) {
  case SET_OK_ADDED_ELEMENT:
    return "SET_OK_ADDED_ELEMENT";
  case SET_ERROR_CANNOT_ADD_ELEMENT:
    return "SET_ERROR_CANNOT_ADD_ELEMENT";
  case SET_ERROR_CANNOT_ADD_ELEMENT_ALREADY_EXISTS:
    return "SET_ERROR_CANNOT_ADD_ELEMENT_ALREADY_EXISTS";
  case SET_ERROR_CANNOT_ADD_ELEMENT_NOT_ADJ:
    return "SET_ERROR_CANNOT_ADD_ELEMENT_NOT_ADJ";
  case SET_EMPTY:
    return "SET_EMPTY";
  }
}

bool set_is_empty(set *ss) { return list_is_empty(ss->l); }

size_t set_size(set *ss) { return ss->l->length; }

set *set_new(int (*compare)(const void *, const void *)) {
  set *ss = (set *)calloc(1, sizeof(set));
  ss->l = list_new(compare);
  return ss;
}

bool set_is_member(set *ss, const void *value) {
  if (list_find(ss->l, value) != NULL)
    return true;
  return false;
}

set_status set_add(set *ss, const void *value) {
  if (set_is_member(ss, value))
    return (set_status){.n = NULL,
                        .status = SET_ERROR_CANNOT_ADD_ELEMENT_ALREADY_EXISTS};

  list_status ls = list_add_last(ss->l, value);

  switch (ls.status) {
  case LIST_OK_ADDED_ELEMENT:
    return (set_status){.n = ls.n, .status = SET_OK_ADDED_ELEMENT};
  case LIST_ERROR_NODES_ARE_NOT_ADJACENTS:
    return (set_status){.n = NULL,
                        .status = SET_ERROR_CANNOT_ADD_ELEMENT_NOT_ADJ};
  default:
    return (set_status){.n = NULL, .status = SET_ERROR_CANNOT_ADD_ELEMENT};
  }
}

int compare_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }

/*
int main(void) {
  int xs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  set *ss = set_new(compare_int);

  set_status stt = set_add(ss, &xs[2]);
  printf("%s\n", set_status_string(stt.status));

  stt = set_add(ss, &xs[2]);
  printf("%s\n", set_status_string(stt.status));

  printf("%d\n", set_size(ss) == 1);

  return EXIT_SUCCESS;
}
*/

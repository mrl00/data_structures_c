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

bool set_is_empty(set *ss) { return list_is_empty(ss); }

size_t set_size(set *ss) { return ss->length; }

set *set_new(int (*compare)(const void *, const void *)) {
  set *ss = (set *)calloc(1, sizeof(set));
  ss = list_new(compare);
  return ss;
}

bool set_is_member(set *ss, const void *value) {
  if (list_find(ss, value) != NULL)
    return true;
  return false;
}

set_status set_add(set *ss, const void *value) {
  if (set_is_member(ss, value))
    return (set_status){.n = NULL,
                        .status = SET_ERROR_CANNOT_ADD_ELEMENT_ALREADY_EXISTS};

  list_status ls = list_add_last(ss, value);

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


#ifndef __SET_H__
#define __SET_H__

#include "list.h"
#include <stdlib.h>

enum SET_STATUS_ENUM {
  SET_OK_ADDED_ELEMENT,
  SET_ERROR_CANNOT_ADD_ELEMENT,
  SET_ERROR_CANNOT_ADD_ELEMENT_ALREADY_EXISTS,
  SET_ERROR_CANNOT_ADD_ELEMENT_NOT_ADJ,
  SET_EMPTY,
};

typedef struct {
  node *n;
  enum SET_STATUS_ENUM status;
} set_status;

typedef list set;

const char *set_status_string(enum SET_STATUS_ENUM);
bool set_is_empty(set *);
size_t set_size(set *);

set *set_new(int (*compare)(const void *, const void *));

bool set_is_member(set *, const void *value);
set_status set_add(set *, const void *value);

#endif

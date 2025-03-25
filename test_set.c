#include "set.h"
#include <stdio.h>

int compare_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }

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
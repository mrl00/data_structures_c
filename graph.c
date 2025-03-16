#include <stdio.h>
#include <stdlib.h>

typedef struct {
  void *element;
} vertex;

vertex *new_vertex(const void *element) {
  vertex *v = (vertex *)calloc(1, sizeof(vertex));
  v->element = element;
  return v;
}

typedef struct {
  vertex *a, *b;
} edge;

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }

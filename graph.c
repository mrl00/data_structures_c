#include <stdio.h>
#include <stdlib.h>

typedef struct {
  void *element;
} vertex;

typedef struct {
  vertex *a, *b;
} edge;

typedef struct graph {
  int (*match)(const edge *);
} graph;

vertex *new_vertex(const void *element);

edge *new_edge(const vertex *, const vertex *);

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }

vertex *new_vertex(const void *element) {
  vertex *v = (vertex *)calloc(1, sizeof(vertex));
  v->element = element;
  return v;
}

edge *new_edge(const vertex *a, const vertex *b) {
  edge *e = (edge *)calloc(1, sizeof(edge));
  e->a = a, e->b = b;
  return e;
}

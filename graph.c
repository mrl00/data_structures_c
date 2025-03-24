#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================
 *                         LIST
 * ============================================================
 */

typedef enum LIST_STATUS_ENUM {
  LIST_OK_ADDED_ELEMENT,
  LIST_ERROR_CANNOT_ADD_ELEMENT,
  LIST_ERROR_NODES_ARE_NOT_ADJACENTS,
  LIST_OK_REMOVED_ELEMENT,
  LIST_ERROR_CANNOT_REMOVE_ELEMENT_NOT_FOUND,
  LIST_EMPTY_LIST,
} list_status;

typedef struct __node {
  void *value;
  struct __node *prev, *next;
} node;

node *node_new(node *prev, node *next, const void *value);

typedef struct __list {
  node *header, *trailer;
  size_t length;
  int (*compare)(const void *, const void *);
} list;

list *list_new(int (*compare)(const void *, const void *));
node *list_find(list *l, const void *x);
bool list_is_empty(list *);

list_status list_add_node_between(node *a, node *b, const void *value);
node *list_first(list *l);
node *list_last(list *l);
list_status list_add_first(list *l, const void *value);
list_status list_add_last(list *l, const void *value);
list_status list_remove(list *l, const void *value);


/*
 * ============================================================
 *                     GRAPH STRUCTS
 * ============================================================
 */

typedef enum VERTEX_STATUS { WHITE, GRAY, BLACK } vertex_status;
typedef enum GRAPH_STATUS {
  OK_ADDED_VERTEX,
  ERROR_CANNOT_ADD_VERTEX,
  ERROR_VERTEX_ALREADY_EXISTS,
  OK_ADDED_EDGE,
  ERROR_CANNOT_ADD_EDGE,
  ERROR_EDGE_ALREADY_EXISTS,
} graph_status;

typedef struct __vertex {
  void *value;
  vertex_status status;
  int distance;
  struct __vertex *predecessor;
  list *adj_list;
} vertex;

typedef struct __edge {
  void *weight;
  vertex *a, *b;
} edge;

typedef struct __graph {
  bool digraph;
  list *vertices;
  list *edges;
  int (*cmp_vtx)(const void *value_1, const void *value_2);
  int (*cmp_edg)(const void *value_1, const void *value_2);
} graph;

vertex *vertex_new(const void *value, int (*)(const void *, const void *));
edge *edge_new(const vertex *vertex_1, const vertex *vertex_2);
graph *graph_new(bool, int (*cmp_vtx)(const void *, const void *),
                 int (*cmp_edg)(const void *, const void *));

graph_status graph_add_vertex(graph *g, const void *value);
graph_status graph_add_edge(graph *g, const void *value_1, const void *value_2);

/*
 * ============================================================
 *                     AUX FUNCTIONS
 * ============================================================
 */
int compare_int(const void *a, const void *b) {
  int a_v = *((int *)a);
  int b_v = *((int *)b);
  return a_v - b_v;
}

int compare_int_vertex(const void *a, const void *b) {
  vertex *v_a = (vertex *)a;
  vertex *v_b = (vertex *)b;
  return compare_int(v_a->value, v_b->value);
}

int compare_int_edge(const void *a, const void *b) {
  edge *e_a = (edge *)a;
  edge *e_b = (edge *)b;
  return (compare_int_vertex(e_a->a, e_b->a) |
          compare_int_vertex(e_a->b, e_b->b));
}

void walk(void **xs, void (*action)(const void *x)) {
  for (void **i = xs; *i != NULL; ++i) {
    action((*i));
  }
}

void print_int(const void *x) { printf("%d ", *((int *)x)); }

void graph_bsf_vertex_prepare_status(const void *s) {
  vertex *ss = (vertex *)s;
  ss->status = WHITE;
  ss->distance = INT_MAX;
  ss->predecessor = NULL;
}

/*
 * ============================================================
 *                           MAIN
 * ============================================================
 */
//int main(int argc, char *argv[]) { return EXIT_SUCCESS; }

/*
 * ============================================================
 *                          GRAPH
 * ============================================================
 */
vertex *vertex_new(const void *element,
                   int (*compare_vertex)(const void *, const void *)) {
  vertex *v = (vertex *)calloc(1, sizeof(vertex));
  v->adj_list = set_new(compare_vertex);
  v->value = (void *)element;
  v->distance = INT_MAX;
  v->predecessor = NULL;
  v->status = WHITE;
  return v;
}

edge *edge_new(const vertex *a, const vertex *b) {
  edge *e = (edge *)calloc(1, sizeof(edge));
  e->a = (vertex *)a, e->b = (vertex *)b;
  return e;
}

graph *graph_new(bool digraph, int (*cmp_vtx)(const void *, const void *),
                 int (*cmp_edg)(const void *, const void *)) {
  graph *g = (graph *)calloc(1, sizeof(graph));
  g->digraph = digraph;
  g->cmp_vtx = cmp_vtx;
  g->cmp_edg = cmp_edg;
  g->vertices = set_new(cmp_vtx);
  g->edges = set_new(cmp_edg);
  return g;
}

graph_status graph_add_vertex(graph *g, const void *value) {

  switch (set_add_element(g->vertices, vertex_new(value, g->cmp_vtx))) {
  OK_ADDED_ELEMENT:
    return OK_ADDED_VERTEX;
  default:
    return ERROR_CANNOT_ADD_VERTEX;
  }
}

graph_status graph_add_edge(graph *g, const void *value_1,
                            const void *value_2) {
  return ERROR_CANNOT_ADD_EDGE;
}
/*
 * ============================================================
 *                     GRAPH ALGORITHMS
 * ============================================================
 */

void graph_bsf(graph *g, vertex *s) {}

void graph_dfs(graph *g) {}
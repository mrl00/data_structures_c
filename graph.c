#include "graph.h"
#include "list.h"
#include "set.h"
#include <stdio.h>

vertex *graph_vertex_new(const void *value) {
  vertex *v = (vertex *)calloc(1, sizeof(vertex));
  v->value = (void *)value;
  return v;
}

vertex_adj *graph_vtx_adj_new(const void *value,
                              int (*cmp_vtx)(const void *, const void *)) {
  vertex_adj *vas = (vertex_adj *)calloc(1, sizeof(vertex_adj));
  vas->v = graph_vertex_new(value);
  vas->adj_list = set_new(cmp_vtx);
  return vas;
}

edge *graph_edge_new(vertex *start, vertex *end, long weight) {
  edge *e = (edge *)calloc(1, sizeof(edge));
  e->start = start, e->end = end, e->weight = weight;
  return e;
}

graph *graph_new(int (*cmp_vtx)(const void *, const void *),
                 int (*cmp_edg)(const void *, const void *),
                 int (*cmp_vtx_adj)(const void *, const void *)) {

  graph *g = (graph *)calloc(1, sizeof(graph));
  g->cmp_vtx = cmp_vtx;
  g->vertex_set = set_new(cmp_vtx_adj);
  g->cmp_edg = cmp_edg;
  g->edge_set = set_new(cmp_edg);
  return g;
}

set *graph_vertices(graph *g) { return g->vertex_set; }
set *graph_edges(graph *g) { return g->edge_set; }

graph_status graph_insert_vertex(graph *g, const void *value) {
  vertex_adj *va = graph_vtx_adj_new(value, g->cmp_vtx);
  set_status ss = set_add(g->edge_set, value);

  switch (ss.status) {
  case SET_ERROR_CANNOT_ADD_ELEMENT_ALREADY_EXISTS:
    return (graph_status){NULL, GRAPH_INSERT_VERTEX_ALREADY_EXISTS};
  case SET_OK_ADDED_ELEMENT:
    return (graph_status){ss.n, GRAPH_INSERT_VERTEX_OK};
  default:
    return (graph_status){NULL, GRAPH_INSERT_VERTEX_CANNOT_INSERT};
  };
}

graph_status graph_insert_edge(graph *g, const void *v1, const void *v2,
                               long weight) {
  node *n1 = list_find(g->vertex_set, v1);
  if (n1 == NULL)
    return (graph_status){NULL, GRAPH_INSERT_EDGE_VERTEX_V1_IS_NOT_A_MEMBER};

  node *n2 = list_find(g->vertex_set, v2);
  if (n2 == NULL)
    return (graph_status){NULL, GRAPH_INSERT_EDGE_VERTEX_V2_IS_NOT_A_MEMBER};

  edge *e = graph_edge_new((vertex *)n1->value, (vertex *)n2->value, weight);

  set_status ss = set_add(g->edge_set, e);

  switch (ss.status) {
  case SET_ERROR_CANNOT_ADD_ELEMENT_ALREADY_EXISTS:
    return (graph_status){NULL, GRAPH_INSERT_EDGE_ALREADY_EXISTS};
  case SET_OK_ADDED_ELEMENT:
    return (graph_status){ss.n, GRAPH_INSERT_EDGE_OK};
  default:
    return (graph_status){NULL, GRAPH_INSERT_EDGE_CANNOT_INSERT};
  }
  return (graph_status){NULL, GRAPH_INSERT_VERTEX_CANNOT_INSERT};
}

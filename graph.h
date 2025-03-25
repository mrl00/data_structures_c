#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "set.h"

typedef struct {
  const void *value;
} vertex;

typedef struct {
  vertex *v;
  set *adj_list;
} vertex_adj;

typedef struct {
  vertex *start, *end;
  long weight;
} edge;

typedef struct {
  bool digraph;
  set *vertex_set;
  int (*cmp_vtx)(const void *, const void *);
  set *edge_set;
  int (*cmp_edg)(const void *, const void *);
} graph;

enum GRAPH_STATUS_ENUM {
  GRAPH_INSERT_VERTEX_OK,
  GRAPH_INSERT_VERTEX_CANNOT_INSERT,
  GRAPH_INSERT_VERTEX_ALREADY_EXISTS,
  GRAPH_INSERT_EDGE_VERTEX_V1_IS_NOT_A_MEMBER,
  GRAPH_INSERT_EDGE_VERTEX_V2_IS_NOT_A_MEMBER,
  GRAPH_INSERT_EDGE_ALREADY_EXISTS,
  GRAPH_INSERT_EDGE_OK,
  GRAPH_INSERT_EDGE_CANNOT_INSERT,
};

typedef struct {
  node *n;
  enum GRAPH_STATUS_ENUM status;
} graph_status;

vertex *graph_vertex_new(const void *);
vertex_adj *graph_vtx_adj_new(const void *,
                              int (*cmp_vtx)(const void *, const void *));

edge *graph_edge_new(vertex *, vertex *, long);

graph *graph_new(int (*cmp_vtx)(const void *, const void *),
                 int (*cmp_edg)(const void *, const void *),
                 int (*cmp_vtx_adj)(const void *, const void *));

set *graph_vertices(graph *g);
set *graph_edges(graph *g);

graph_status graph_insert_vertex(graph *, const void *);
graph_status graph_insert_edge(graph *, const void *, const void *, long);

graph_status graph_vertices_are_adj(graph *, vertex *, vertex *);

#endif // !__GRAPH_H__

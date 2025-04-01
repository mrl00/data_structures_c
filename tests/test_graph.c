#include "../graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int cmp_vtx(const void *a, const void *b) {
  return cmp_int(((vertex *)a)->value, ((vertex *)b)->value);
}

int cmp_edg(const void *a, const void *b) {
  edge *x = (edge *)a, *y = (edge *)b;
  return cmp_vtx(x->start, y->start) | cmp_vtx(x->end, y->end);
}

int cmp_vtx_adj(const void *a, const void *b) {
  vertex_adj *s = (vertex_adj *)a, *t = (vertex_adj *)b;
  return cmp_vtx(s->v, t->v);
}

void test_create_vertex() {
  int xs[] = {1};
  vertex *v = graph_vertex_new(&xs[0]);
  assert((*(int *)v->value) == 1);
}

void test_vertex_adj() {
  int xs[] = {1, 2, 3, 4};
  vertex_adj *va = graph_vtx_adj_new(&xs[0], &cmp_vtx);
  assert((*(int *)va->v->value) == 1);
  assert(cmp_int(&xs[3], &xs[3]) == 0);

  set_add(va->adj_list, graph_vertex_new(&xs[1]));
  set_add(va->adj_list, graph_vertex_new(&xs[2]));
  set_add(va->adj_list, graph_vertex_new(&xs[3]));

  int k = 2;
  for (node *i = list_first(va->adj_list); i != va->adj_list->trailer;
       i = i->next) {
    vertex *v = (vertex *)i->value;
    assert(*(int *)v->value == k++);
  }
}

void test_create_edge() {
  int xs[] = {1, 2};
  edge *e =
      graph_edge_new(graph_vertex_new(&xs[0]), graph_vertex_new(&xs[1]), 1);
  assert((*(int *)e->start->value) == 1 && (*(int *)e->end->value) == 2 &&
         e->weight == 1);
}

void test_create_graph() {
  int xs[] = {1, 2, 3, 4};

  graph *g = graph_new(true, cmp_vtx, cmp_edg, cmp_vtx_adj);
  assert(g->digraph);

  vertex *v1 = graph_vertex_new(&xs), *v2 = graph_vertex_new(&xs[1]),
         *v3 = graph_vertex_new(&xs[2]), *v4 = graph_vertex_new(&xs[3]);
  assert(g->cmp_vtx(v1, v2) != 0);

  vertex_adj *va1 = graph_vtx_adj_new(&xs, g->cmp_vtx);
  vertex_adj *va2 = graph_vtx_adj_new(&xs[1], g->cmp_vtx);
  vertex_adj *va3 = graph_vtx_adj_new(&xs[2], g->cmp_vtx);

  set_add(g->vertex_set, va1);
  set_add(g->vertex_set, va2);
  set_add(g->vertex_set, va3);

  int k = 1;
  for (node *i = list_first(graph_vertices(g));
       i != list_trailer(graph_vertices(g)); i = i->next) {
    vertex_adj *s = (vertex_adj *)i->value;
    assert(*(int *)s->v->value == k++);
  }

  edge *e1 = graph_edge_new(v1, v2, 1), *e2 = graph_edge_new(v3, v4, 1);
  edge *e3 = graph_edge_new(v1, v3, 1), *e4 = graph_edge_new(v2, v4, 1);
  assert(g->cmp_edg(e1, e2) != 0);

  set_add(g->edge_set, e1);
  set_add(g->edge_set, e2);
  set_add(g->edge_set, e3);
  set_add(g->edge_set, e4);

  assert(graph_edges(g)->length == 4);
}

void test_insert_vertex() {
  int xs[] = {1, 2, 3, 4};

  vertex *v1 = graph_vertex_new(&xs);

  graph *g = graph_new(true, cmp_vtx, cmp_edg, cmp_vtx_adj);
  assert(g->digraph);

  graph_status gs = graph_insert_vertex(g, &xs);
  assert(gs.status == GRAPH_INSERT_VERTEX_OK);
  assert(graph_vertices(g)->length == 1);

  gs = graph_insert_vertex(g, &xs);
  assert(gs.status == GRAPH_INSERT_VERTEX_ALREADY_EXISTS);
  assert(graph_vertices(g)->length == 1);

  node *n1 =
      list_find(graph_vertices(g), graph_vtx_adj_new(v1->value, g->cmp_vtx));

  assert(n1 != NULL);
  printf("find vtx adj by value: %d\n",
         *(int *)((vertex_adj *)n1->value)->v->value);

  gs = graph_insert_edge(g, &xs[1], &xs[2], 1);
}

int main(void) {

  test_create_vertex();
  test_vertex_adj();
  test_create_edge();
  test_create_graph();
  test_insert_vertex();

  return EXIT_SUCCESS;
}

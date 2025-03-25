#include "graph.h"
#include <assert.h>

int cmp_int(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int cmp_vtx(const void *a, const void *b) {
  vertex *v_a = (vertex *)a;
  vertex *v_b = (vertex *)b;
  return cmp_int(v_a->value, v_b->value);
}

int main(void) {
  int xs1[] = {1};

  vertex *v = graph_vertex_new(&xs1[0]);
  assert((*(int *)v->value) == 1);

  int xs2[] = {1, 2};
  edge *e =
      graph_edge_new(graph_vertex_new(&xs2[0]), graph_vertex_new(&xs2[1]), 1);
  assert((*(int *)e->start->value) == 1 && (*(int *)e->end->value) == 2 &&
         e->weight == 1);

  int xs3[] = {1, 2, 3, 4};
  vertex_adj *va = graph_vtx_adj_new(&xs3[0], &cmp_vtx);
  assert((*(int *)va->v->value) == 1);

  set_add(va->adj_list, &xs3[1]);
  set_status ss = set_add(va->adj_list, &xs3[2]);
  // set_add(va->adj_list, &xs3[3]);

  // int k = 2;
  // for (node *i = va->adj_list->l->header->next; i->next != NULL;
  //    i = i->next, k++)
  // assert((*(int *)i->value) == k);

  return EXIT_SUCCESS;
}


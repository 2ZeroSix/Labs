#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

#include <stdio.h>
#include <stdlib.h>

#define vrt_kl short // тип необходимый для хранения индекса вершины
#define len_kl int // тип необходимый для хранения длины ребра
#define edge_index_kl int // тип необходимый для хранения индекса ребра
#define maxN 5000
#define minN 0
#define maxM(N) ( (N) * ( (N) - 1 ) / 2 )
#define minM 0

typedef struct _edge_kl {
	vrt_kl a;
	vrt_kl b;
	len_kl weight;
}edge_kl;

typedef struct _queue_kl {
  edge_kl* edge;
  struct _queue_kl* next;
}queue_kl;

int sort_edge_i_kl(const edge_kl* edge1, const edge_kl* edge2);

vrt_kl find_dj_kl(vrt_kl* p, vrt_kl x);

void unite_dj_kl(vrt_kl* p, vrt_kl x, vrt_kl y);

vrt_kl* create_dj_kl(vrt_kl count);

void add_que_kl(queue_kl** que, edge_kl* edge);

edge_kl* del_que_kl(queue_kl** que);

void print_queue_kl(FILE* out, queue_kl** que);

queue_kl* search_kl(edge_kl* gh, vrt_kl* p, vrt_kl N, edge_index_kl M);

edge_kl* read_kl(FILE* in, vrt_kl* N, edge_index_kl* M);

void complete_kl(FILE* in, FILE* out);


#endif
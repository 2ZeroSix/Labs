#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "binary_heap.h"

#define dij_edge_index int
#define dij_vrt_index short
#define dij_len int
#define dij_maxlen INT_MAX
#define dij_overmaxlen (dij_len)-2
#define dij_overflow (dij_len)-3
#define dij_empty (dij_len)-1
#define dij_maxN 5000
#define dij_minN 0
#define dij_maxM(N) ( (N) * ( (N) - 1 ) / 2 )
#define dij_minM 0

enum DIJ_ERR_CODES {
	OK = 0,
	BAD_NUM_OF_VERS,
	BAD_NUM_OF_EDGES,
	BAD_VERTEX,
	BAD_LENGTH,
	BAD_NUM_OF_LINES,
} dij_err; //последняя ошибка

/**
 * последняя ошибка
 * @return строка с описанием последней ошибки
 */
const char * dij_error();

/**
 * освобождение памяти из под графа в виде матрице смежности
 * @param gh граф в виде матрицы смежности
 * @param N  кол-во вершин
 */
void dij_free_graph(dij_len* gh[], dij_vrt_index N);

/**
 * инициализация графа в виде матрицы смежности
 * @param  empty_sign признак пустого ребра
 * @param  N          кол-во вершин
 * @return            граф в виде матрицы смежности
 */
dij_len** dij_init_graph(dij_len empty_sign, dij_vrt_index N);

/**
 * вывод расстояний до вершин (с учётом dij_empty, dij_overmaxlen, dij_overflow)
 * @param out  выходной файл
 * @param dist массив с расстояниями
 * @param N    кол-во вершин
 */
void	dij_write_lengths(FILE* out, dij_len* dist, dij_vrt_index N);

/**
 * вывод пути до вершины
 * @param out    выходной файл
 * @param parent массив предков
 * @param distF  расстояние до вершины (с учётом dij_empty, dij_overmaxlen, dij_overflow)
 * @param S      начальная вершина
 * @param F      конечная вершина
 */
void dij_write_path(FILE* out, dij_vrt_index* parent, dij_len distF, dij_vrt_index S, dij_vrt_index F);

/**
 * операция сравнения (с учётом dij_empty, dij_overmaxlen, dij_overflow)
 * 0 < 1 < ... < INT_MAX < overflow < overmaxlen < empty
 * @param  a вес 1
 * @param  b вес 2
 * @return   1 если a <  b
 *           0 если a == b
 *          -1 если a >  b
 */
int dij_cmp(const int* a, const int* b);

/**
 * релаксация исходящих рёбер
 * @param gh    	граф в виде матрицы смежности
 * @param N     	кол-во вершин
 * @param bheap		указатель на структуру бинарной кучи
 * @param parent	массив предков
 * @param jmin  	номер вершины, от которой совершать релаксации
 * @param wmin  	расстояние до вершины, от которой совершать релаксации
 */
void dij_upd_que_graph(dij_len** gh, dij_vrt_index N, heap* bheap, dij_vrt_index* parent, dij_vrt_index jmin, dij_len wmin);

/**
 * алгоритм Дейкстры
 * @param  gh   граф в виде матрицы смежности
 * @param  N    кол-во вершин
 * @param  S    начальная вершина
 * @param  dist указатель, по которому будет присвоен массив с расстояниями до вершин (если NULL, то ничего записано не будет)
 * @return      массив предков
 */
dij_vrt_index* dij_dijkstra(dij_len** gh, dij_vrt_index N, dij_vrt_index S, dij_len** dist);

/**
 * чтение входного файла с информацией о графе и вершинах, между которыми нужно найти кратчайший путь
 * @param  in входной файл
 * @param  N  указатель на память, в которую записать кол-во вершину		(не NULL)
 * @param  S  указатель на память, в которую записать начальную вершину	(не NULL)
 * @param  F  указатель на память, в которую записать конечную вершину	(не NULL)
 * @return    граф в виде матрицы смежности
 */
dij_len** dij_read(FILE* in, dij_vrt_index* N, dij_vrt_index* S, dij_vrt_index* F);

/**
 * придумать описание
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void dij_complete(FILE* in, FILE* out);


#endif
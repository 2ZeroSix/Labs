#ifndef _PRIM_H_
#define _PRIM_H_

#include <stdio.h>
#include <stdlib.h>

#define pr_edge_index int
#define pr_vrt_index short
#define pr_len int
#define pr_EMPTY -1
#define maxN 5000
#define minN 0
#define maxM(N) ( (N) * ( (N) - 1 ) / 2 )
#define minM 0

enum PR_ERR_CODES {
	OK = 0,
	BAD_NUM_OF_VERS,
	BAD_NUM_OF_EDGES,
	BAD_VERTEX,
	BAD_LENGTH,
	BAD_NUM_OF_LINES,
	NO_SPANNING_TREE
} pr_err; //последняя ошибка

/**
 * последняя ошибка
 * @return строка с описанием последней встреченной ошибки
 */
const char* pr_error();

typedef _pr_edges{
	pr_vrt_index b; // конец ребра
	pr_len val; // вес ребра
	_pr_edges* next;
}pr_edges;

typedef _pr_graph{
	pr_edges* edges; // список рёбер при вершине
	pr_vrt_index count; // кол-во рёбер при вершине
}

typedef _pr_que_graph{
	pr_vrt_index a;
	pr_len weight;
}pr_que_graph;

/**
 * очистка памяти из под графа
 * @param gh указатель на граф
 * @param N  кол-во вершин
 */
void pr_free_graph(pr_len* gh[], pr_vrt_index N);

/**
 * вывод минимального остовного дерева
 * @param out   указатель на выходной файл
 * @param mingh массив в котором по индексам начал рёбер лежат индексы концов рёбер
 * @param N     кол-во вершин
 */
void pr_write_mst(FILE* out, pr_vrt_index* mingh, pr_vrt_index N);

/**
 * поиск минимального остоввного дерева по алгоритму Прима
 * @param  gh ненулевой указатель на граф
 * @param  N  кол-во вершин
 * @return    массив в котором по индексам начал рёбер лежат индексы концов рёбер (составляющие минимальное остовное дерево)
 *            признаком отсутствия ребра является равенство индекса элемента массива со значением
 */
pr_vrt_index* pr_mst(pr_len* gh[], pr_vrt_index N);

/**
 * чтение графа из файла
 * @param  in ненулевой указатель на входной файл
 * @param  N  ненулевой указатель на область памяти под кол-во вершин
 * @param  M  ненулевой указатель на область памяти под кол-во рёбер
 * @return    массив рёбер
 */
pr_len** pr_read(FILE* in, pr_vrt_index* N);

/**
 * полное построение минимального каркаса графа из входного файла и вывод его в выходной
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void pr_complete(FILE* in, FILE* out);

#endif
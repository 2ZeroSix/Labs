#ifndef _PRIM_H_
#define _PRIM_H_

#include <stdio.h>
#include <stdlib.h>
#include "binary_heap.h"

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

/**
 * инициализация графа
 * @param  N кол-во вершин
 * @return   граф из N вершин без связей
 */
pr_len** pr_init_graph(pr_vrt_index N);

/**
 * очистка памяти из под графа
 * @param gh граф
 * @param N  кол-во вершин
 */
void pr_free_graph(pr_len** gh, pr_vrt_index N);

/**
 * вывод минимального остовного дерева
 * @param out   указатель на выходной файл
 * @param mingh массив в котором по индексам начал рёбер лежат индексы концов рёбер
 * @param N     кол-во вершин
 */
void pr_write_mst(FILE* out, pr_vrt_index* mingh, pr_vrt_index N);

/**
 * операция сравнения весов с учётом pr_EMPTY
 * @param  a вес
 * @param  b вес
 * @return	 >0 если b > a
 *           =0 если b = a
 *           <0 если b < a
 */
int primcmp(const int* a, const int* b);

/**
 * обновление минимальных расстояний до вершин
 * @param gh    граф
 * @param N     кол-во вершин
 * @param bheap указатель на бинарную кучу
 * @param mingh массив предков
 * @param jmin  от какой вершины обновлять
 */
void pr_upd_que_graph(pr_len** gh, pr_vrt_index N, heap* bheap, pr_vrt_index* mingh, pr_vrt_index jmin);

/**
 * поиск минимального остовного дерева по алгоритму Прима
 * @param  gh граф
 * @param  N  кол-во вершин
 * @return    массив предков
 */
pr_vrt_index* pr_mst(pr_len** gh, pr_vrt_index N);

/**
 * чтение графа из файла
 * @param  in ненулевой указатель на входной файл
 * @param  N  ненулевой указатель на область памяти под кол-во вершин
 * @param  M  ненулевой указатель на область памяти под кол-во рёбер
 * @return    граф
 */
pr_len** pr_read(FILE* in, pr_vrt_index* N);

/**
 * полное построение минимального каркаса графа из входного файла и вывод его в выходной
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void pr_complete(FILE* in, FILE* out);

#endif
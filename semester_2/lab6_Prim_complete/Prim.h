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

/**
 * последняя ошибка
 * @return строка с описанием последней встреченной ошибки
 */
char * pr_error();

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
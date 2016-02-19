#ifndef TOP_SORT_GRAPH_H
#define TOP_SORT_GRAPH_H
#include <stdio.h>
#include <stdlib.h>

#define maxN 1000
#define minN 0

typedef struct _graph_tsg {
	int N; // кол-во вершин
	int M; // кол-во рёбер
	char* color;
	int* a; // массив начал рёбер
	int* b;	// массив концов рёбер
}graph_tsg;

/**
 * последняя ошибка
 * @return строка с описанием последней ошибки
 */
char* error_tsg();

/**
 * очистка памяти из под грава
 * @param gh ненулевой указатель на граф
 */
void free_graph_tsg(graph_tsg* gh);

/**
 * вывод массива целых чисел в поток
 * @param  out  ненулевой указатель на поток
 * @param  vertices массив целых чисел (может быть NULL)
 */
void print_tsg(FILE* out, int* vertices);

/**
 * тополоогическая сортировка графа
 * @param  es граф вида
 * @return    Если возможно отсортировать, то отсортированный массив вершин; иначе NULL.
 */
int* sort_tsg(graph_tsg* gh);

/**
 * чтение графа из потока
 * @param  in ненулевой указатель на поток
 * @param  N  ненулевой указатель на память под хранение кол-ва вершин
 * @param  M  ненулевой указатель на память под хранение кол-ва рёбер
 * @return    Если корректные данные, то массив рёбер; Иначе NULL.
 */
graph_tsg* read_tsg(FILE* in);

/**
 * чтение из потока, топологическая сортировка и вывод (включая информацию об ошибках)
 * @param  in  ненулевой указатель на поток ввода
 * @param  out ненулевой указатель на поток вывода
 *  */
void complete_tsg(FILE* in, FILE* out);
#endif
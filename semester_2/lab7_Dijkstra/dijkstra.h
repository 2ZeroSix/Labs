#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include <stdio.h>
#include <stdlib.h>

#define dij_edge_index int
#define dij_vrt_index short
#define dij_len int
#define dij_MAXlen INT_MAX
#define dij_overMAXlen -2
#define dij_EMPTY -1
#define dij_maxN 5000
#define dij_minN 0
#define dij_maxM(N) ( (N) * ( (N) - 1 ) / 2 )
#define dij_minM 0

// /**
//  * последняя ошибка
//  * @return строка с описанием последней встреченной ошибки
//  */
// char * dij_error();

// /**
//  * очистка памяти из под графа
//  * @param gh указатель на граф
//  * @param N  кол-во вершин
//  */
// void dij_free_graph(dij_len* gh[], dij_vrt_index N);



// /**
//  * чтение графа из файла
//  * @param  in ненулевой указатель на входной файл
//  * @param  N  ненулевой указатель на область памяти под кол-во вершин
//  * @param  M  ненулевой указатель на область памяти под кол-во рёбер
//  * @return    массив рёбер
//  */

/**
 * придумать описание
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void dij_complete(FILE* in, FILE* out);


#endif
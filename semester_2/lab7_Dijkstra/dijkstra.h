#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include <stdio.h>
#include <stdlib.h>

#define dij_edge_index int
#define dij_vrt_index short
#define dij_len int
#define dij_MAXlen INT_MAX
#define dij_overMAXlen (short)-2
#define dij_overflow (short)-3
#define dij_EMPTY (short)-1
#define dij_maxN 5000
#define dij_minN 0
#define dij_maxM(N) ( (N) * ( (N) - 1 ) / 2 )
#define dij_minM 0


/**
 * придумать описание
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void dij_complete(FILE* in, FILE* out);


#endif
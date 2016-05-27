#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define dij_edge_index int
#define dij_vrt_index short
#define dij_len int
#define dij_MAXlen INT_MAX
#define dij_overMAXlen (dij_len)-2
#define dij_overflow (dij_len)-3
#define dij_EMPTY (dij_len)-1
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
 * придумать описание
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void dij_complete(FILE* in, FILE* out);


#endif
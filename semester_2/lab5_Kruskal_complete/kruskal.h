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

enum KL_ERR_CODES {
	OK = 0,
	BAD_NUM_OF_VERS,
	BAD_NUM_OF_EDGES,
	BAD_VERTEX,
	BAD_LENGTH,
	BAD_NUM_OF_LINES,
	NO_SPANNING_TREE
} err_kl; //последняя ошибка

/**
 * последняя ошибка
 * @return строка с описанием последней встреченной ошибки
 */
const char * error_kl();

/**
 * функция сравнения рёбер по весу
 * @param  edge1 первое ребро
 * @param  edge2 второе ребро
 * @return       Если вес первого больше веса второго, то > 0;
 *               Если их вес равен, то 0;
 *               Иначе < 0.
 */
int sort_edge_i_kl(const edge_kl* edge1, const edge_kl* edge2);


//////////////////////////////////////
//Система непересекающихся множеств //
//////////////////////////////////////

typedef struct _disjoint_set_kl {
	vrt_kl p; // родительская вершина
	vrt_kl h; // глубина дерева (ранг)
}disjoint_set_kl;

/**
 * определение к какому множеству принадлежит элемент
 * @param  djs массив структур (родительская вершина; ранг)
 * @param  x   элемент одного из множеств
 * @return     представитель мн-ва, которому принадлежит данный элемент
 */
vrt_kl find_dj_kl(disjoint_set_kl* djs, vrt_kl x);

/**
 * объединение множеств (случайное)
 * @param djs массив структур (родительская вершина; ранг) 
 * @param x   элемент одного из множеств
 * @param y   элемент одного из множеств
 */
void unite_dj_kl(disjoint_set_kl* djs, vrt_kl x, vrt_kl y);

/**
 * создание массива хранящего указанное количество одноэлементных множеств
 * @param  count кол-во множеств
 * @return       массив структур для хранения указанного кол-ва множеств 
 */
disjoint_set_kl* create_dj_kl(vrt_kl count);

//////////////////////
//работа с очередью //
//////////////////////

/**
 * добавление элемента в очередь
 * @param que  указатель на очередь
 * @param edge новый элемент
 */
void add_que_kl(queue_kl** que, edge_kl* edge);

/**
 * удаление элемента из очереди
 * @param  que указатель на очередь
 * @return     Если очередь ненулевая, то указатель удалённый из очереди элемент;
 *             Иначе NULL.
 */
edge_kl* del_que_kl(queue_kl** que);

/**
 * вывод очереди в файл
 * @param out ненулевой указатель на выходной файл
 * @param que указатель на указатель на очередь
 */
void print_queue_kl(FILE* out, queue_kl** que);

///////////////////
//Основная часть //
///////////////////

/**
 * поиск минимального каркаса графа
 * @param  gh  ненулевой указатель на граф
 * @param  djs массив структур (родительская вершина; ранг) 
 * @param  N   кол-во вершин
 * @param  M   кол-во рёбер
 * @return     очередь содержащая минимальный каркас графа
 */
queue_kl* search_kl(edge_kl* gh, disjoint_set_kl* djs, vrt_kl N, edge_index_kl M);

/**
 * чтение графа из файла
 * @param  in ненулевой указатель на входной файл
 * @param  N  ненулевой указатель на область памяти под кол-во вершин
 * @param  M  ненулевой указатель на область памяти под кол-во рёбер
 * @return    массив рёбер
 */
edge_kl* read_kl(FILE* in, vrt_kl* N, edge_index_kl* M);

/**
 * полное построение минимального каркаса графа из входного файла и вывод его в выходной
 * @param in  ненулевой указатель на входной файл
 * @param out ненулевой указатель на выходной файл
 */
void complete_kl(FILE* in, FILE* out);


#endif
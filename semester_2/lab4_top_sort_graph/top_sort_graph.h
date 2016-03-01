#ifndef TOP_SORT_GRAPH_H
#define TOP_SORT_GRAPH_H
#include <stdio.h>
#include <stdlib.h>

#define maxN 1000
#define minN 0
#define maxM N*(N-1)
#define minM 0
	
typedef struct _stack_graph_tsg {
  short vertice;
  struct _stack_graph_tsg* next;
}stack_graph_tsg;

typedef struct _graph_tsg {
	char color; //цвет вершины (нужен при сортировке)
	stack_graph_tsg* edge; //список номеров вершин в которые есть пути
}graph_tsg;


typedef struct _stack {
  short value;
  struct _stack* next;
}stack;

/**
 * последняя ошибка
 * @return строка с описанием последней ошибки
 */
char *error_tsg();

stack* pop_tsg(stack** head);
void push_tsg(stack** head, int val);
void free_stack_tsg(stack** head);
void revert_stack_tsg(stack** head);

char depth_sort_tsg(graph_tsg* gh, int pos, stack** stk);

stack* sort_tsg(FILE* out, graph_tsg* gh, int count);

stack_graph_tsg* push_stack_graph_tsg(graph_tsg gh, int b);

/**
* чтение графа из потока
* @param  in ненулевой указатель на поток
* @param  N  ненулевой указатель на память под хранение кол-ва вершин
* @param  M  ненулевой указатель на память под хранение кол-ва рёбер
* @return    Если корректные данные, то массив рёбер; Иначе NULL.
*/
graph_tsg* read_tsg(FILE* in, int *count);

void print_tsg(FILE* out, stack* stk);

/**
* очистка памяти из под графа
* @param gh ненулевой указатель на граф
*/
void free_graph_tsg(graph_tsg* gh, int count);

/**
 * чтение из потока, топологическая сортировка и вывод (включая информацию об ошибках)
 * @param  in  ненулевой указатель на поток ввода
 * @param  out ненулевой указатель на поток вывода
 *  */
void complete_tsg(FILE* in, FILE* out);
#endif
#ifndef TOP_SORT_GRAPH_H
	#define TOP_SORT_GRAPH_H
	#include <stdio.h>
	#include <stdlib.h>

	#define maxN 1000
	#define minN 0
	#define maxM N*(N-1)
	#define minM 0

	// список, который используется для хранения вершин, в которые можно попасть из данной
	typedef struct _stack_graph_tsg {
	  short vertice; // номер вершины
	  struct _stack_graph_tsg* next;
	}stack_graph_tsg;

	enum TSG_ERR_CODES {
		OK = 0,
		BAD_NUM_OF_VERS,
		BAD_NUM_OF_EDGES,
		BAD_VERTEX,
		BAD_NUM_OF_LINES,
		IMPOSSIBLE_TO_SORT
	} err_tsg; //последняя ошибка

	typedef struct _graph_tsg {
		enum COLOR_VER {VER_NOT_USED, VER_USED, VER_ADDED} color; //цвет вершины (нужен при сортировке)
		stack_graph_tsg* edge; //список номеров вершин в которые есть пути
	}graph_tsg;


	/**
	 * последняя ошибка
	 * @return строка с описанием последней ошибки
	 */
	const char *error_tsg();

	//стек и операции с ним
	typedef struct _stack {
	  short value;
	  struct _stack* next;
	}stack;
	stack* pop_tsg(stack** head);
	void push_tsg(stack** head, int val);
	void free_stack_tsg(stack** head);

	/**
	 * занос вершин в стек в отсортированном порядке проходом в глубину
	 * @param  gh    ненулевой массив вершин со списком, в котором хранятся номера вершин в которые есть прямые пути
	 * @param  pos элемент от которого начинать проход
	 * @param  stk ненулевой указатель на стек
	 * @return     Если пройдено, то 1;
	 *             Иначе 0 (если обнаружен цикл)
	 */
	char depth_sort_tsg(graph_tsg* gh, int pos, stack** stk);

	/**
	 * топологическая сортировка графа
	 * @param  out   ненулевой указатель на выходной файл
	 * @param  gh    ненулевой массив вершин со списком, в котором хранятся номера вершин в которые есть прямые пути
	 * @param  count кол-во вершин
	 * @return       стек содержащий в себе отсортированный топологически граф
	 */
	stack* sort_tsg(FILE* out, graph_tsg* gh, int count);

	/**
	 * добавление вершины в список вершин
	 * @param  gh вершина со списком, в котором хранятся вершины, в которые есть доступные пути
	 * @param  b  вершина
	 * @return    новое указатель на голову списка
	 */
	stack_graph_tsg* push_stack_graph_tsg(graph_tsg gh, int b);

	/**
	 * чтение графа из потока
	 * @param  in    ненулевой указатель на входной
	 * @param  count указатель на область памяти, в который будет записано кол-во вершин в графе(будет записано, только если кол-во вершин корректно)
	 * @return       Если корректные данные, указатель на область памяти, в которой хранится граф;
	 *               Иначе NULL.
	*/
	graph_tsg* read_tsg(FILE* in, int *count);

	/**
	 * вывод значений хранящихся в списке и его очистка
	 * @param out ненулевой указатель на выходной файл
	 * @param stk указатель на список
	 */
	void print_tsg(FILE* out, stack* stk);

	/**
	 * очистка памяти из под графа
	 * @param  gh    ненулевой массив вершин со списком, в котором хранятся номера вершин в которые есть прямые пути
	*/
	void free_graph_tsg(graph_tsg* gh, int count);

	/**
	 * чтение из потока, топологическая сортировка и вывод (включая информацию об ошибках)
	 * @param  in  ненулевой указатель на поток ввода
	 * @param  out ненулевой указатель на поток вывода
	 *  */
	void complete_tsg(FILE* in, FILE* out);
#endif

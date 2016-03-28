#define _CRT_SECURE_NO_WARNINGS
#include "top_sort_graph.h"

#define TSG_PROCESS_ERROR(err) {\
	err_tsg = err;\
	return NULL;\
}

enum TSG_ERR_CODES {
	OK = 0,
	BAD_NUM_OF_VERS,
	BAD_NUM_OF_EDGES,
	BAD_VERTEX,
	BAD_NUM_OF_LINES,
	IMPOSSIBLE_TO_SORT
} err_tsg = OK; //последняя ошибка

const char* err_tsg_dcp[6] = { //описания ошибок
	"", //0
	"bad number of vertices", //1
	"bad number of edges", //2
	"bad vertex", //3
	"bad number of lines", //4
	"impossible to sort"}; //5

const char * error_tsg() {
	return err_tsg_dcp[err_tsg];
}

stack* pop_tsg(stack** head) {
	stack* temp = NULL;
	if (head)
	{
		temp = *head;
		if (*head)
			*head = (*head)->next;
	}
	return temp;
}

void push_tsg(stack** head, int val) {
	if (head)
	{
		stack* push = (stack*)calloc(1, sizeof(stack));
		push->value = val;
		push->next = *head;
		(*head) = push; 
	}
	return;
}

void free_stack_tsg(stack** head) {
	while(head && (*head))
	{
		stack* temp;
		temp = (*head);
		(*head) = (*head)->next;
		free(temp);
	}
}

char depth_sort_tsg(graph_tsg* gh, int pos, stack** stk) {
	stack_graph_tsg* cur = gh[pos].edge;
	gh[pos].color = VER_USED; // пометка о посещении вершины
	while(cur){
		if(gh[cur->vertice].color == VER_NOT_USED) { // если не был в вершине ни разу
			if (!depth_sort_tsg(gh, cur->vertice, stk)) {
				return 0;
			}
		}
		else if(gh[cur->vertice].color == VER_USED) { // если уже был в вершине в этой рекурсии
			return 0;
		}
		cur = cur->next;
	}
	gh[pos].color = VER_ADDED; // пометка о том, что вершина уже в списке
	push_tsg(stk, pos);
	return 1;
}

stack* sort_tsg(FILE* out, graph_tsg* gh, int count) {
	short	 i;
	stack* stk = NULL;
	for(i = 0; i < count; i++) {
		if (gh[i].color != VER_ADDED) { // если вершина ещё не в списке
			if(!depth_sort_tsg(gh, i, &stk)) { // если найден цикл
				free_stack_tsg(&stk);
				TSG_PROCESS_ERROR(IMPOSSIBLE_TO_SORT);
			}
		}
	}
	return stk;
}

stack_graph_tsg* push_stack_graph_tsg(graph_tsg gh, int b) {
	stack_graph_tsg* cur = (stack_graph_tsg*)calloc(1, sizeof(stack_graph_tsg));
	cur->vertice = b;
	cur->next = gh.edge;
	return cur;
}

graph_tsg* read_tsg(FILE* in, int *count) {
	int N; // число вершин
	int M; // число рёбер
	int i, a, b;
	graph_tsg* gh = NULL;
	if(fscanf(in, "%d%d", &N, &M) < 2) { // если нет числа рёбер или вершин
		TSG_PROCESS_ERROR(BAD_NUM_OF_LINES);
	}
	else {
		if ((N >= minN) && (N <= maxN)) { //1 ошибка
			*count = N;
		}
		else {
			TSG_PROCESS_ERROR(BAD_NUM_OF_VERS);
		}
		if ((M < minN) || (M > maxM)) { //2 ошибка
			TSG_PROCESS_ERROR(BAD_NUM_OF_EDGES);
		}
		gh = (graph_tsg*)calloc(N, sizeof(graph_tsg));
	}
	for (i = 0; i < M; i++) {
		if(fscanf(in, "%d%d", &a, &b) < 2) { //4 ошибка
			free_graph_tsg(gh, *count);
			TSG_PROCESS_ERROR(BAD_NUM_OF_LINES);
		}
		if((a <= minN) || (a > N) || (b <= minN) || (b > N)) { //3 ошибка
			free_graph_tsg(gh, *count);
			TSG_PROCESS_ERROR(BAD_VERTEX);
		}
		a--; //для удобной работы с массивами
		b--;
		gh[a].edge = push_stack_graph_tsg(gh[a], b);
	}
	return gh;
}

void print_tsg(FILE* out, stack* stk) {
	stack* temp = NULL;
	while((temp = pop_tsg(&stk))) {
		fprintf(out, "%d ", temp->value + 1); // +1 для восстановления значения полученного на входе, изменённого для удобства работы с массивами
		free(temp);
	}
}

//очистка памяти из под списка в одной вершине
void free_one_graph_tsg(graph_tsg gh) {
	stack_graph_tsg* cur = gh.edge;
	while(cur){
		stack_graph_tsg* prev = cur;
		cur = cur->next;
		free(prev);
	}
}

void free_graph_tsg(graph_tsg* gh, int count) {
	int i;
	for (i = 0; i < count; i++){
		free_one_graph_tsg(gh[i]);
	}
	free(gh);
}

void complete_tsg(FILE* in, FILE* out) {
	int count;
	graph_tsg* gh;
	err_tsg = OK;
	if(((gh = read_tsg(in, &count))) && count) {
		stack* stk = sort_tsg(out ,gh, count);
		free_graph_tsg(gh, count);
		print_tsg(out ,stk);
	}
	fprintf(out, "%s", error_tsg());
}

#define _CRT_SECURE_NO_WARNINGS
#include "top_sort_graph.h"

static unsigned char err_tsg = 0; //number of last error
static char* err_tsg_dcp[6] = { //error description
	"", //0
	"bad number of vertices", //1
	"bad number of edges", //2
	"bad vertex", //3
	"bad number of lines", //4
	"impossible to sort"}; //5

char * error_tsg() {
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
	stack* temp;
	while(head && (*head))
	{
		temp = (*head);
		(*head) = (*head)->next;
		free(temp);
	}
}

void revert_stack_tsg(stack** head) {
	stack *cur = NULL, *prev1 = NULL, *prev2 = NULL;
	if(*head)
		cur = *head;
	while(cur)
	{ 
		if(prev1)
		{
			prev1->next = prev2; 
		}
		prev2 = prev1;
		prev1 = cur;
		cur = cur->next;
	}
	if (prev1)
		prev1->next = prev2;
	*head = prev1;
	return;
}

char depth_sort_tsg(graph_tsg* gh, int pos, stack** stk) {
	stack_graph_tsg* cur = gh[pos].edge;
	gh[pos].color = 1;
	while(cur){
		if(gh[cur->vertice].color == 0) {
			if (!depth_sort_tsg(gh, cur->vertice, stk)) {
				return 0;
			}
		}
		else if(gh[cur->vertice].color == 1) {
			return 0;
		}
		cur = cur->next;
	}
	gh[pos].color = 2;
	push_tsg(stk, pos);
	return 1;
}

stack* sort_tsg(FILE* out, graph_tsg* gh, int count) {
	int i;
	stack* stk = NULL;
	for(i = 0; i < count; i++) {
		if (gh[i].color != 2) {
			if(!depth_sort_tsg(gh, i, &stk)) {
				free_stack_tsg(&stk);
				err_tsg = 5;
				return NULL;
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
	int M; // число
	int i, a, b;
	graph_tsg* gh = NULL;
	switch(fscanf(in, "%d%d", &N, &M)) {
	case -1:
		err_tsg = 4;
		return NULL;
		break;
	case 0: 
		err_tsg = 4;
		return NULL;
		break;
	case 1:
		if ((N >= minN) && (N <= maxN)) { //1 ошибка
			*count = N;
		}
		else {
			err_tsg = 1;
			return NULL;
		}
		gh = (graph_tsg*)calloc(N, sizeof(graph_tsg));
		break;
	default:
		if ((N >= minN) && (N <= maxN)) { //1 ошибка
			*count = N;
		}
		else {
			err_tsg = 1;
			return NULL;
		}
		if ((M < minN) || (M > maxM)) { //2 ошибка
			err_tsg = 2;
			return NULL;
		}
		gh = (graph_tsg*)calloc(N, sizeof(graph_tsg));
		break;
	}
	for (i = 0; i < M; i++) {
		if(fscanf(in, "%d%d", &a, &b) < 2) { //4 ошибка
			free_graph_tsg(gh, *count);
			err_tsg = 4;
			return NULL;
		}
		if((a < minN) || (a > N) || (b < minN) || (b > N)) { //3 ошибка
			free_graph_tsg(gh, *count);
			err_tsg = 3;
			return NULL;
		}
		gh[--a].edge = push_stack_graph_tsg(gh[a], --b);
	}
	return gh;
}

void print_tsg(FILE* out, stack* stk) {
	stack* temp = NULL;
	while((temp = pop_tsg(&stk))) {
		fprintf(out, "%d ", temp->value + 1);
		free(temp);
	}
}

void free_one_graph_tsg(graph_tsg* gh) {
	stack_graph_tsg* cur = gh->edge;
	while(cur){
		stack_graph_tsg* prev = cur;
		cur = cur->next;
		free(prev);
	}
}

void free_graph_tsg(graph_tsg* gh, int count) {
	int i;
	for (i = 0; i < count; i++){
		free_one_graph_tsg(&(gh[i]));
	}
	free(gh);
}

void complete_tsg(FILE* in, FILE* out) {
	int count;
	graph_tsg* gh;
	if(((gh = read_tsg(in, &count))) && count) {
		stack* stk = sort_tsg(out ,gh, count);
		free_graph_tsg(gh, count);
		print_tsg(out ,stk);
	}
	fprintf(out, "%s", error_tsg());
}
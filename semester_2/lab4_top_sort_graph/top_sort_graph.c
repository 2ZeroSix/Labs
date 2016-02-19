#include "top_sort_graph.h"

static unsigned char err_tsg = 0; //number of last error
static char** err_tsg_dcp = { //error description
	"", //0
	"bad number of vertices", //1
	"bad number of edges", //2
	"bad vertex", //3
	"bad number of lines", //4
	"impossible to sort"}; //5

char* error_tsg() {
	return err_tsg_dcp[err_tsg];
}

int readint(FILE* in) {
	char c;
	int num = 0;
	while (isdigit(c = getc(in))) {
		num = num * 10 + c - '0';
	}
	return num;
}

void free_graph_tsg(graph_tsg* gh) {
	free(gh->a);
	free(gh->b);
	free(gh->color);
	free(gh);
}

void print_tsg(FILE* out, int* vertices) {

}

char

int* sort_tsg(graph_tsg* gh) {
	int i;
	int* stk = (int*)calloc(1, sizeof(int));
	for (i = 0; i < gh->N; i++) {
		if(!check_vtc(gh, i)) {
			free(stk);
			return NULL;
		}
	}
	return stk;
}

graph_tsg* read_tsg(FILE* in) {
	int i;
	graph_tsg* gh = (graph_tsg*)calloc(1, sizeof(graph_tsg));
	fscanf(in, "%d", &(gh->N));
	if(!((gh->N >= minN) && (gh->N <= maxN))) {
		err_tsg = 1;
		free(gh);
		return NULL;
	}
	fscanf(in, "%d", &(gh->M));
	if(!((gh->M >= 1) && (gh->M <= (gh->N * (gh->N + 1) / 2)))) {
		err_tsg = 2;
		free(gh);
		return NULL;
	}
	gh->a = (int*)calloc(gh->M, sizeof(int));
	gh->b = (int*)calloc(gh->M, sizeof(int));
	for (i = 0; i < gh->M; i++) {
		gh->a[i] = readint(in);
		if(feof(in)) {
			free_graph_tsg(gh);
			err_tsg = 4;
			return NULL;
		}
		gh->b[i] = readint(in);
		if ((gh->a[i] >= gh->N) || (gh->b[i] >= gh->N)) {
			free_graph_tsg(gh);
			err_stg = 3;
			return NULL;
		}
		gh->color = (char*)calloc(N, sizeof(char));
	}
	return gh;
}

void complete_tsg(FILE* in, FILE* out) {
	graph_tsg* gh = read_tsg(in);
	int* vtc = sort_tsg(gh);
	free_graph_tsg(gh);
	print_tsg(out, vtc);
	free(vtc);
}
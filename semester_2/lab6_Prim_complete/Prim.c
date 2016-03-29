#define _CRT_SECURE_NO_WARNINGS

#include "Prim.h"

#define PR_PROCESS_ERROR(err) {\
	pr_err = err;\
	return NULL;\
}

const char* pr_err_dcp[7] = { //описания ошибок
	"", //0
	"bad number of vertices", //1
	"bad number of edges", //2
	"bad vertex", //3
	"bad length", //4
	"bad number of lines", //5
	"no spanning tree"}; //6

const char * pr_error() {
	return pr_err_dcp[pr_err];
}

pr_edges* pr_add_edges(pr_edges* edges, b, weight) {
	pr_edges* tmp = (pr_edges*)calloc(1, sizeof(pr_edges));
	tmp->b = b;
	tmp->val = weight;
	tmp->next = edges;
	return tmp;
}

void pr_add_graph(graph* gh, a, b, weight) {
	gh[a]->edges = pr_add_edges(gh[a]->edges, b, weight);
	gh[a]->count++;
}

void pr_free_edges(pr_edges* edges) {
	if(edges) {
		while(edges) {
			pr_edges* tmp = edges;
			edges = edges->next;
			free(tmp);
		}
	}
}

void pr_free_graph(pr_len* gh[], pr_vrt_index N) {
	pr_vrt_index i;
	for (i = 0; i < N; i++) {
		pr_free_edges(gh[i]->edges);
	}
	free(gh);
}

void pr_write_mst(FILE* out, pr_vrt_index* mingh, pr_vrt_index N) {
	pr_vrt_index i;
	for (i = 0; i < N; i++) {
		if(mingh[i] != i)
			fprintf(out, "%hd %hd\n", i + 1, mingh[i] + 1);
	}
}

void pr_insert_que_graph(pr_que_graph* min, pr_vrt_index count, )

void pr_add_que_graph(pr_que_graph* min, pr_vrt_index count, graph* gh, pr_vrt_index a) {
	pr_edges* tmp = gh[a].edges;
	pr_insert_que_graph(min, count, a, 0)
	while (tmp) {
		pr_insert_que_graph(min, count, a, tmp)
	}
}

pr_vrt_index* pr_mst(graph* gh, pr_vrt_index N) {
	if(N) {
		pr_que_graph* min = (pr_que_graph*)calloc(N, sizeof(pr_que_graph));
		char* used = (char*)calloc(N, sizeof(char));
		pr_vrt_index* mingh = (pr_vrt_index*)calloc(N, sizeof(pr_vrt_index));
		pr_vrt_index i, count = 0;
		for (i = 0; i < N; i++) {
			mingh[i] = i;
		}
		pr_add_que_graph(min, count, gh, 0);
		for(i = 0; i < N; i++) {
			pr_vrt_index jmin;
			jmin = pr_pop_que_graph(min, count);
			if (jmin == -1) {
				pr_free_que_graph(min, count);
				free(used);
				free(mingh);
				PR_PROCESS_ERROR(NO_SPANNING_TREE);
			}
			used[jmin] = 1;
			pr_upd_que_graph(min, count, mingh, used, &(gh[jmin]));
		}
		free(min);
		free(used);
		return mingh;
	}
	return NULL;
}


graph* pr_read(FILE* in, pr_vrt_index* N) {
	pr_edge_index i, M;
	pr_vrt_index a, b;
	graph* gh;
	pr_len weight;
	if(fscanf(in, "%hd%d", N, &M) < 2) { //5 ошибка
		PR_PROCESS_ERROR(BAD_NUM_OF_LINES);
	}
	else {
		if ((*N < minN) || (*N > maxN)) { //1 ошибка
			PR_PROCESS_ERROR(BAD_NUM_OF_VERS);
		}
		if ((M < minM) || (M > maxM(*N))) { //2 ошибка
			PR_PROCESS_ERROR(BAD_NUM_OF_EDGES);
		}
		if(*N == 0) {
			PR_PROCESS_ERROR(NO_SPANNING_TREE);
		}
	}
	gh = (graph*)calloc(*N, sizeof(graph));
	for (i = 0; i < M; i++) {
		if(fscanf(in, "%hd%hd%d", &(a), &(b), &(weight)) < 3) { //5 ошибка
			pr_free_graph(gh, *N);
			PR_PROCESS_ERROR(BAD_NUM_OF_LINES);
		}
		if((a <= minN) || (a > *N) || (b <= minN) || (b > *N)) { //3 ошибка
			pr_free_graph(gh, *N);
			PR_PROCESS_ERROR(BAD_VERTEX);
		}
		if((weight < 0)) { // 4 ошибка
			pr_free_graph(gh, *N);
			PR_PROCESS_ERROR(BAD_LENGTH);
		}
		pr_add_graph(gh, a, b, weight);
		pr_add_graph(gh, b, a, weight);	
	}
	return gh;
}


void pr_complete(FILE* in, FILE* out) {
	pr_vrt_index N;
	graph* gh;
	if((gh = pr_read(in, &N))) {
		pr_vrt_index* mingh;
		if((mingh = pr_mst(gh, N))) {
			pr_write_mst(out, mingh, N);
			free(mingh);
		}
		pr_free_graph(gh, N);
	}
	fprintf(out, "%s\n", pr_error());
}

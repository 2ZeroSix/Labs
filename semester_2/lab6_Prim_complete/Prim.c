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

void pr_free_graph(pr_len* gh[], pr_vrt_index N) {
	pr_vrt_index i;
	for (i = 0; i < N; i++) {
		free(gh[i]);
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

pr_vrt_index* pr_mst(pr_len* gh[], pr_vrt_index N) {
	if(N) {
		pr_len* min = (pr_len*)calloc(N, sizeof(pr_len));
		char* used = (char*)calloc(N, sizeof(char));
		pr_vrt_index* mingh = (pr_vrt_index*)calloc(N, sizeof(pr_vrt_index));
		pr_vrt_index i;
		for (i = 0; i < N; i++) {
			mingh[i] = i;
			min[i] = pr_EMPTY;
		}
		min[0] = 0;
		for(i = 0; i < N; i++) {
			pr_vrt_index j, jmin = -1;
			for(j = 0; j < N; j++) {
				if(!used[j] && (jmin == -1 || min[j] <= min[jmin]) && (min[j] != pr_EMPTY)) jmin = j;
			}
			if (jmin == -1) {
				free(min);
				free(used);
				free(mingh);
				PR_PROCESS_ERROR(NO_SPANNING_TREE);
			}
			used[jmin] = 1;
			for(j = 0; j < N; j++) {
				if(!used[j] && ((gh[jmin][j] < min[j]) || ((min[j] == pr_EMPTY)))) {
					min[j] = gh[jmin][j];
					mingh[j] = jmin;
				}
			}
		}
		free(min);
		free(used);
		return mingh;
	}
	return NULL;
}


pr_len** pr_read(FILE* in, pr_vrt_index* N) {
	pr_edge_index i, M;
	pr_vrt_index a, b;
	pr_len** gh;
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
	gh = (pr_len**)calloc(*N, sizeof(pr_len*));
	for(i = 0; i < *N; i++) {
		pr_vrt_index j;
		gh[i] = (pr_len*)calloc(*N, sizeof(pr_len));
		for(j = 0; j < *N; j++) {
			gh[i][j] = pr_EMPTY;
		}
	}
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
		gh[b - 1][a - 1] = gh[a - 1][b - 1] = weight;
	}
	for(i = 0; i < *N; i++) {
		int j;
		for(j = 0; j < *N; j++) {
		}
	}
	return gh;
}


void pr_complete(FILE* in, FILE* out) {
	pr_vrt_index N;
	pr_len** gh;
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

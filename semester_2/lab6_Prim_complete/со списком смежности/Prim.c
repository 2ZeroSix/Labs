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

pr_edges* pr_add_edges(pr_edges* edges, pr_vrt_index b, pr_len weight) {
	pr_edges* tmp = (pr_edges*)malloc(sizeof(pr_edges));
	tmp->b = b;
	tmp->val = weight;
	tmp->next = edges;
	return tmp;
}

void pr_add_graph(pr_graph* gh, pr_vrt_index a, pr_vrt_index b, pr_len weight) {
	gh[a].edges = pr_add_edges(gh[a].edges, b, weight);
}

void pr_free_edges(pr_edges* edges) {
	while(edges) {
		pr_edges* tmp = edges;
		edges = edges->next;
		free(tmp);
	}
}

void pr_free_graph(pr_graph* gh, pr_vrt_index N) {
	pr_vrt_index i;
	for (i = 0; i < N; i++) {
		pr_free_edges(gh[i].edges);
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

// a < b
int primcmp(const int* a, const int* b) {
	return (*a == pr_EMPTY) ? ((*b == pr_EMPTY) ? 0 : -1) : ((*b == pr_EMPTY) ? 1 : *b - *a);
}

void pr_upd_que_graph(pr_graph* gh, heap* bheap, pr_vrt_index* mingh, pr_vrt_index jmin) {
	pr_edges* cur = gh[jmin].edges;
	while(cur) {
		if (primcmp(&(cur->val), &(((int*)bheap->array)[pos_by_id(bheap, cur->b)])) > 0) {
			if(update_by_index(bheap, cur->b, &(cur->val))) mingh[cur->b] = jmin;
		}
		cur = cur->next;
	}
}

pr_vrt_index* pr_mst(pr_graph* gh, pr_vrt_index N) {
	if(N) {
		pr_len* min = (pr_len*)malloc(N * sizeof(pr_len));
		pr_vrt_index* mingh = (pr_vrt_index*)malloc(N * sizeof(pr_vrt_index));
		pr_vrt_index i;
		heap* bheap;
		for (i = 0; i < N; i++) {
			mingh[i] = i;
			min[i] = pr_EMPTY;
		}
		min[0] = 0;
		bheap = build_heap(min, N, N, sizeof(pr_len), (int (*)(const void*, const void*))primcmp);
		for(i = 0; i < N; i++) {
			pr_vrt_index jmin;
			pr_len wmin;
			//id
			jmin = id_by_pos(bheap, 0);
			//weight
			wmin = *(pr_len*)get_max(bheap);
			if (wmin == pr_EMPTY) {
				del_heap(bheap, 0);
				free(mingh);
				PR_PROCESS_ERROR(NO_SPANNING_TREE);
			}
			pr_upd_que_graph(gh, bheap, mingh, jmin);
		}
		del_heap(bheap, 0);
		return mingh;
	}
	return NULL;
}


pr_graph* pr_read(FILE* in, pr_vrt_index* N) {
	pr_edge_index i, M;
	pr_graph* gh;
		pr_len weight[8];
		pr_vrt_index a[8], b[8];
		char count;
	if(fscanf(in, "%hd%d", N, &M) < 2) {
		PR_PROCESS_ERROR(BAD_NUM_OF_LINES);
	}
	if ((*N < minN) || (*N > maxN)) {
		PR_PROCESS_ERROR(BAD_NUM_OF_VERS);
	}
	if ((M < minM) || (M > maxM(*N))) {
		PR_PROCESS_ERROR(BAD_NUM_OF_EDGES);
	}
	if(*N == 0) {
		PR_PROCESS_ERROR(NO_SPANNING_TREE);
	}
	gh = (pr_graph*)calloc(*N, sizeof(pr_graph));
	M = M / 8 + ((M % 8) ? 1 : 0);
	for (i = 0; i < M ; i++) {
		if(((count = fscanf(in, "%hd%hd%d%hd%hd%d%hd%hd%d%hd%hd%d%hd%hd%d%hd%hd%d%hd%hd%d%hd%hd%d", &(a[0]), &(b[0]), &(weight[0]) , &(a[1]), &(b[1]), &(weight[1]) , &(a[2]), &(b[2]), &(weight[2]) , &(a[3]), &(b[3]), &(weight[3]) , &(a[4]), &(b[4]), &(weight[4]) , &(a[5]), &(b[5]), &(weight[5]) , &(a[6]), &(b[6]), &(weight[6]) , &(a[7]), &(b[7]), &(weight[7]))) % 3) || (count <= 0)) {
			// printf("%d\n", count);
			pr_free_graph(gh, *N);
			PR_PROCESS_ERROR(BAD_NUM_OF_LINES);
		}
		// printf("%d\n", count);
		count /= 3;
		for (--count; count >= 0; --count) {
			if((a[count] <= minN) || (a[count] > *N) || (b[count] <= minN) || (b[count] > *N)) {
				pr_free_graph(gh, *N);
				PR_PROCESS_ERROR(BAD_VERTEX);
			}
			if((weight[count] < 0)) {
				pr_free_graph(gh, *N);
				PR_PROCESS_ERROR(BAD_LENGTH);
			}
			a[count]--;
			b[count]--;
			pr_add_graph(gh, a[count], b[count], weight[count]);
			pr_add_graph(gh, b[count], a[count], weight[count]);
		}
	}
	return gh;
}


void pr_complete(FILE* in, FILE* out) {
	pr_vrt_index N;
	pr_graph* gh;
	if((gh = pr_read(in, &N))) {
		// printf("start\n");
		pr_vrt_index* mingh;
		if((mingh = pr_mst(gh, N))) {
			pr_write_mst(out, mingh, N);
			// printf("complete\n");
			free(mingh);
		}
		pr_free_graph(gh, N);
	}
	fprintf(out, "%s\n", pr_error());
}

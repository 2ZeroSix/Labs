#define _CRT_SECURE_NO_WARNINGS

#include "dijkstra.h"
#include "binary_heap.h"

#define DIJ_PROCESS_ERROR(err) {\
	dij_err = err;\
	return NULL;\
}

static char* dij_err_dcp[6] = { //описания ошибок
	"", //0
	"bad number of vertices", //1
	"bad number of edges", //2
	"bad vertex", //3
	"bad length", //4
	"bad number of lines"}; //5

char * dij_error() {
	return dij_err_dcp[dij_err];
}

void dij_free_graph(dij_len* gh[], dij_vrt_index N) {
	dij_vrt_index i;
	for (i = 0; i < N; i++) {
		free(gh[i]);
	}
	free(gh);
}

dij_len** dij_init_graph(dij_len empty_sign, dij_vrt_index N) {
	dij_vrt_index i, j;
	dij_len** gh;
	gh = (dij_len**)calloc(N, sizeof(dij_len*));
	for(i = 0; i < N; i++) {
		gh[i] = (dij_len*)calloc(N, sizeof(dij_len));
		for(j = 0; j < N; j++) {
			gh[i][j] = empty_sign;
		}
	}
	return gh;
}

void	dij_write_lengths(FILE* out, dij_len* dist, dij_vrt_index N) {
	dij_vrt_index i;
	for(i = 0; i < N; i++) {
		switch (dist[i]) {
			case dij_EMPTY:
				fprintf(out, "oo ");
				break;
			case dij_overMAXlen:
				fprintf(out, "INT_MAX+ ");
				break;
			case dij_overflow:
				fprintf(out, "INT_MAX+ ");
				break;
			default:
				fprintf(out, "%d ", dist[i]);
				break;
		}
	}
}

void dij_write_path(FILE* out, dij_vrt_index* parent, dij_len distS, dij_vrt_index S, dij_vrt_index F) {
	switch(distS) {
		case dij_EMPTY:
			fprintf(out, "no path\n");
			break;
		case dij_overflow:
			fprintf(out, "overflow\n");
			break;
		default:
			fprintf(out, "%hd ", F + 1);
			while(F != S) {
				F = parent[F];
				fprintf(out, "%hd ", F + 1);
			}
			fprintf(out, "\n");
			break;
	}
}

// ((a < b) ? 1 : ((a == b) ? 0 : -1))
// 0 < 1 < ... < INT_MAX < overflow < INT_MAX+ < empty
int dij_cmp(const int* a, const int* b) {
	if (*a == dij_EMPTY) {
		return (*b == dij_EMPTY) ? 0 : -1;
	}
	else if (*b == dij_EMPTY) {
		return 1;
	}
	else if(*a == dij_overMAXlen) {
		return (*b == dij_overMAXlen) ? 0 : -1;
	}
	else if(*b == dij_overMAXlen) {
		return 1;
	}
	else if (*a == dij_overflow) {
		return (*b == dij_overflow) ? 0 : -1;
	}
	else if (*b == dij_overflow) {
		return 1;
	}
	else {
		return *b - *a;
	}
}

void dij_upd_que_graph(dij_len** gh, dij_vrt_index N, heap* bheap, dij_vrt_index* mingh, dij_vrt_index jmin, dij_len wmin) {
	dij_vrt_index i;
	for( i = 0; i < N; ++i) {
		dij_len new_range;
		dij_len old_range = ((int*)bheap->array)[pos_by_id(bheap, i)];
		dij_len edge = gh[jmin][i];
		if (wmin == dij_overflow) {
			new_range = dij_overflow;
		}
		else if (edge == dij_EMPTY) {
			new_range = dij_EMPTY;
		}
		else if ((wmin == dij_overMAXlen) || ((wmin - (INT_MAX - edge)) > 0)) {
			if (old_range == dij_overMAXlen) {
				new_range = dij_overflow;
			}
			else {
				new_range = dij_overMAXlen;
			}
		}
		else {
			new_range = wmin + edge;
		}
		if (dij_cmp(&(new_range), &(old_range)) > 0) {
			if(update_by_index(bheap, i, &(new_range))) mingh[i] = jmin;
		}
	}
}

dij_vrt_index* dij_dijkstra(dij_len** gh, dij_vrt_index N, dij_vrt_index S, dij_len** dist) {
	if(N) {
		dij_len* min_distance = (dij_len*)calloc(N, sizeof(dij_len));
		dij_len* distance = (dij_len*)calloc(N, sizeof(dij_len));
		dij_vrt_index* parent = (dij_vrt_index*)calloc(N, sizeof(dij_vrt_index));
		dij_vrt_index i;
		heap* bheap;
		for (i = 0; i < N; i++) {
			parent[i] = i;
			distance[i] = dij_EMPTY;
			min_distance[i] = dij_EMPTY;
		}
		// printf("%d\n", S);
		min_distance[S] = 0;
		bheap = build_heap(min_distance, N, N, sizeof(dij_len), (int (*)(const void*, const void*))dij_cmp);
		for(i = 0; i < N; i++) {
			// for (int j = 0; j < N; j++) {
			// 	printf("%d : %d; ", parent[j], min_distance[pos_by_id(bheap, j)]);
			// }
			// printf("\n");
			dij_vrt_index jmin;
			dij_len wmin;
			jmin = id_by_pos(bheap, 0);
			distance[jmin] = wmin = *(dij_len*)get_max(bheap);
			if(wmin == dij_EMPTY) {
				del_heap(bheap, 0);
				*dist = distance;
				return parent;
			}
			dij_upd_que_graph(gh, N, bheap, parent, jmin, wmin);
		}
		del_heap(bheap, 0);
		*dist = distance;
		return parent;
	}
	else {
		return NULL;
	}
}


dij_len** dij_read(FILE* in, dij_vrt_index* N, dij_vrt_index* S, dij_vrt_index* F) {
	dij_edge_index i, M;
	dij_vrt_index a, b;
	dij_len** gh;
	dij_len weight;
	// printf("read\n");
	// printf("fscanf\n");
	if(fscanf(in, "%hd%hd%hd%d", N, S, F, &M) < 4) { //5 ошибка
		DIJ_PROCESS_ERROR(BAD_NUM_OF_LINES);
	}
	// printf("check\n");
	if ((*N < dij_minN) || (*N > dij_maxN)) { //1 ошибка
		DIJ_PROCESS_ERROR(BAD_NUM_OF_VERS);
	}
	if ((M < dij_minM) || (M > dij_maxM(*N))) { //2 ошибка
		DIJ_PROCESS_ERROR(BAD_NUM_OF_EDGES);
	}
	if((*S <= dij_minN) || (*S > *N) || (*F <= dij_minN) || (*F > *N)) { //3 ошибка
		DIJ_PROCESS_ERROR(BAD_VERTEX);
	}
	// printf("init\n");
	gh = dij_init_graph(dij_EMPTY, *N);
	// printf("for\n");
	for (i = 0; i < M; i++) {
		if(fscanf(in, "%hd%hd%d", &(a), &(b), &(weight)) < 3) { //5 ошибка
			dij_free_graph(gh, *N);
			DIJ_PROCESS_ERROR(BAD_NUM_OF_LINES);
		}
		if((a <= dij_minN) || (a > *N) || (b <= dij_minN) || (b > *N)) { //3 ошибка
			dij_free_graph(gh, *N);
			DIJ_PROCESS_ERROR(BAD_VERTEX);
		}
		if((weight < 0)) { // 4 ошибка
			dij_free_graph(gh, *N);
			DIJ_PROCESS_ERROR(BAD_LENGTH);
		}
		gh[b - 1][a - 1] = gh[a - 1][b - 1] = weight;
	}
	for(i = 0; i < *N; i++) {
		int j;
		for(j = 0; j < *N; j++) {
		}
	}
	(*S)--;
	(*F)--;
	return gh;
}

void dij_complete(FILE* in, FILE* out) {
	dij_len** gh;
	dij_vrt_index N, S, F;
	// printf("dij start\n");
	if(gh = dij_read(in, &N, &S, &F)) {
		dij_vrt_index* parent;
		dij_len* dist;
		// printf("complete read\nN: %hd; S: %hd; F: %hd\n", N, S, F);
		if(parent = dij_dijkstra(gh, N, S, &dist)) {
			// printf("complete dijkstra\n");
			dij_write_lengths(out, dist, N);
			fprintf(out, "\n");
			// printf("lengths wrote\n");
			dij_write_path(out, parent, dist[F], S, F);
			// printf("path wrote\n");
			free(dist);
			free(parent);
		}
		dij_free_graph(gh, N);
	}
	// printf("dij end\n");
	fprintf(out, "%s", dij_error());
}

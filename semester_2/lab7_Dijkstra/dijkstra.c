#define _CRT_SECURE_NO_WARNINGS

#include "dijkstra.h"

static unsigned char dij_err = 0; //номер последней ошибки
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

dij_vrt_index* dij_dijkstra(dij_len** gh, dij_vrt_index N, dij_vrt_index S, dij_len** dist) {
	if(!N) {
		return NULL;
	}
		dij_len* distance = (dij_len*)calloc(N, sizeof(dij_len));
		char* used = (char*)calloc(N, sizeof(char));
		dij_vrt_index* parent = (dij_vrt_index*)calloc(N, sizeof(dij_vrt_index));
		dij_vrt_index i;
		for (i = 0; i < N; i++) {
			parent[i] = i;
			distance[i] = dij_EMPTY;
		}
		distance[S] = 0;
		for(i = 0; i < N; i++) {
			int jmin = -1, j;
			for(j = 0; j < N; j++) {
				if(!used[j] && (distance[j] != dij_EMPTY) && ((jmin == -1) || (distance[j] <= distance[jmin]))) {
					jmin = j;
				}
			}
			if(jmin == -1) {
				free(used);
			if(dist){
				*dist = distance;
			}
			else {
				free(distance);
			}				
				return parent;
			}
			used[jmin] = 1;
			for(j = 0; j < N; j++) {
				if((distance[j] == dij_EMPTY) || ((distance[jmin] + gh[jmin][j] < distance[j]) && (gh[jmin][j] > 0) && (distance[jmin] >= 0))) {
					// printf("distance[%d] = %d\n",j, distance[j]);
					// printf("distance[%d] = %d\n",jmin, distance[jmin]);
					// printf("gh[%hd][%hd] = %d\n", jmin, j, gh[jmin][j]);
					if(((((dij_MAXlen - distance[jmin]) >= gh[jmin][j])) || (distance[j] == dij_EMPTY)) && (distance[jmin] != dij_overMAXlen)){
						distance[j] = distance[jmin] + gh[jmin][j];
					}
					else {
						if((distance[j] == dij_overMAXlen) || (distance[j] == dij_overflow)) {
							distance[j] = dij_overflow;
						}
						else {
							distance[j] = dij_overMAXlen;							
						}
					}
					parent[j] = jmin;
				}
			}
			// printf("\n");
		}
		if(dist){
			*dist = distance;
		}
		else {
			free(distance);
		}
		free(used);
		return parent;
}


dij_len** dij_read(FILE* in, dij_vrt_index* N, dij_vrt_index* S, dij_vrt_index* F) {
	dij_edge_index i, M;
	dij_vrt_index a, b;
	dij_len** gh;
	dij_len weight;
	// printf("read\n");
	// printf("fscanf\n");
	if(fscanf(in, "%hd%hd%hd%d", N, S, F, &M) < 4) { //5 ошибка
		dij_err = 5;
		return NULL;
	}
	else {
		// printf("check\n");
		if ((*N < dij_minN) || (*N > dij_maxN)) { //1 ошибка
			dij_err = 1;
			return NULL;
		}
		if ((M < dij_minM) || (M > dij_maxM(*N))) { //2 ошибка
			dij_err = 2;
			return NULL;
		}
		if((*S <= dij_minN) || (*S > *N) || (*F <= dij_minN) || (*F > *N)) { //3 ошибка
			dij_err = 3;
			return NULL;
		}
	}
	// printf("init\n");
	gh = dij_init_graph(dij_EMPTY, *N);
	// printf("for\n");
	for (i = 0; i < M; i++) {
		if(fscanf(in, "%hd%hd%d", &(a), &(b), &(weight)) < 3) { //5 ошибка
			dij_free_graph(gh, *N);
			dij_err = 5;
			return NULL;
		}
		if((a <= dij_minN) || (a > *N) || (b <= dij_minN) || (b > *N)) { //3 ошибка
			dij_free_graph(gh, *N);
			dij_err = 3;
			return NULL;
		}
		if((weight < 0)) { // 4 ошибка
			dij_free_graph(gh, *N);
			dij_err = 4;
			return NULL;
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

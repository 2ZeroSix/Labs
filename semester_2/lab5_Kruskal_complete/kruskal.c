#define _CRT_SECURE_NO_WARNINGS

#include "kruskal.h"

#define KL_PROCESS_ERROR(err) {\
	err_kl = err;\
	return NULL;\
}

const char* err_kl_dcp[7] = { //описания ошибок
	"", //0
	"bad number of vertices", //1
	"bad number of edges", //2
	"bad vertex", //3
	"bad length", //4
	"bad number of lines", //5
	"no spanning tree"}; //6

const char * error_kl() {
	return err_kl_dcp[err_kl];
}

int sort_edge_i_kl(const edge_kl* edge1, const edge_kl* edge2) {
	return edge1->weight - edge2->weight;
}

vrt_kl find_dj_kl(disjoint_set_kl* djs, vrt_kl x) {
    if (djs[x].p == x) return x;
    return djs[x].p = find_dj_kl(djs, djs[x].p);
}

void unite_dj_kl(disjoint_set_kl* djs, vrt_kl x, vrt_kl y) {
  x = find_dj_kl(djs, x);
  y = find_dj_kl(djs, y);
  if (x != y) {
		if (djs[x].h < djs[y].h) {
			vrt_kl tmp = x;
			x = y;
			y = tmp;
		}
		djs[y].p = x;
		if (djs[x].h == djs[y].h)
			++djs[x].h;
	}
}

disjoint_set_kl* create_dj_kl(vrt_kl count) {
	disjoint_set_kl* djs = (disjoint_set_kl*)calloc(count, sizeof(disjoint_set_kl));
	vrt_kl i;
	for(i = 0; i < count; i++) {
		djs[i].p = i;
	}
	return djs;
}

void add_que_kl(queue_kl** que, edge_kl* edge) {
	if(que) {	
		queue_kl* new = (queue_kl*)calloc(1, sizeof(queue_kl));
		new->edge = edge;
		if(*que) {
			while((*que)->next) {
				*que = (*que)->next;
			}
			(*que)->next = new;
		}
		else {
			*que = new;
		}
	}
}

edge_kl* del_que_kl(queue_kl** que) {
	if (que && *que) {
		edge_kl* tmp = (*que)->edge;
		queue_kl* prev = *que;
		(*que) = (*que)->next;
		free(prev);
		return tmp;
	}
	else {
		return NULL;
	}
}

void print_queue_kl(FILE* out, queue_kl **que) {
	edge_kl* tmp;
	while((tmp = del_que_kl(que))) {
		fprintf(out, "%hd %hd\n", tmp->a + 1, tmp->b + 1);
	}
}

queue_kl* search_kl(edge_kl* gh, disjoint_set_kl* djs, vrt_kl N, edge_index_kl M) {
	edge_index_kl i;
	queue_kl* que = NULL;
	queue_kl* que_end;
	if (M > 0) {
		add_que_kl(&que, &(gh[0]));
		unite_dj_kl(djs, gh[0].a, gh[0].b);
	}
	que_end = que;
	for(i = 1; i < M; i++) {
		if(find_dj_kl(djs, gh[i].a) != find_dj_kl(djs, gh[i].b)) {
			add_que_kl(&que_end, &(gh[i]));
			unite_dj_kl(djs, gh[i].a, gh[i].b);
		}
	}
	for(i = 1; i < N; i++) {
		if (find_dj_kl(djs, i) != find_dj_kl(djs, i - 1)) {
			free(que);
			KL_PROCESS_ERROR(NO_SPANNING_TREE);
		}
	}
	return que;
}

edge_kl* read_kl(FILE* in, vrt_kl* N, edge_index_kl* M) {
	edge_index_kl i;
	edge_kl* gh;
	if(fscanf(in, "%hd%d", N, M) < 2) { //5 ошибка
		KL_PROCESS_ERROR(BAD_NUM_OF_LINES);
	}
	else {
		if ((*N < minN) || (*N > maxN)) { //1 ошибка
			KL_PROCESS_ERROR(BAD_NUM_OF_VERS);
		}
		if ((*M < minM) || (*M > maxM(*N))) { //2 ошибка
			KL_PROCESS_ERROR(BAD_NUM_OF_EDGES);
		}
		if(*N == 0) {
			KL_PROCESS_ERROR(NO_SPANNING_TREE);
		}
	}
	gh = (edge_kl*)calloc(*M, sizeof(edge_kl));
	for (i = 0; i < *M; i++) {
		if(fscanf(in, "%hd%hd%d", &(gh[i].a), &(gh[i].b), &(gh[i].weight)) < 3) { //5 ошибка
			free(gh);
			KL_PROCESS_ERROR(BAD_NUM_OF_LINES);
		}
		if((gh[i].a <= minN) || (gh[i].a > *N) || (gh[i].b <= minN) || (gh[i].b > *N)) { //3 ошибка
			free(gh);
			KL_PROCESS_ERROR(BAD_VERTEX);
		}
		if((gh[i].weight < 0)) { // 4 ошибка
			free(gh);
			KL_PROCESS_ERROR(BAD_LENGTH);
		}
		gh[i].a--;
		gh[i].b--;
	}
	return gh;
}

void complete_kl(FILE* in, FILE* out) {
	edge_kl* gh;
	vrt_kl N;
	edge_index_kl M;
	err_kl = OK;
	if ((gh = read_kl(in, &N, &M))) {
		disjoint_set_kl* djs = create_dj_kl(N);
		queue_kl* que;
		qsort(gh, M, sizeof(edge_kl), (int(*) (const void*, const void*)) sort_edge_i_kl);
		if((que = search_kl(gh, djs, N, M))) {
			print_queue_kl(out, &que);
		}
		free(gh);
		free(djs);
	}
	printf("%s", error_kl());
}
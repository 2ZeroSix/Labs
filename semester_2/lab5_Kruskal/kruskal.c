#include "kruskal.h"


static unsigned char err_tsg = 0; //номер последней ошибки
static char* err_tsg_dcp[7] = { //описания ошибок
	"", //0
	"bad number of vertices", //1
	"bad number of edges", //2
	"bad vertex", //3
	"bad length", //4
	"bad number of lines", //5
	"no spanning tree"}; //6

char * error_tsg() {
	return err_tsg_dcp[err_tsg];
}

int sort_edge_i_kl(const edge_kl* edge1, const edge_kl* edge2) {
	return edge1->weight - edge2->weight;
}

vrt_kl find_dj_kl(vrt_kl* p, vrt_kl x) {
    if (p[x] == x) return x;
    return p[x] = find_dj_kl(p, p[x]);
}

void unite_dj_kl(vrt_kl* p, vrt_kl x, vrt_kl y) {
  x = find_dj_kl(p, x);
  y = find_dj_kl(p, y);
  if (rand() & 1)
    p[x] = y;
  else
  {
    p[y] = x;
  }
}

vrt_kl* create_dj_kl(vrt_kl count) {
	vrt_kl* p = (vrt_kl*)calloc(count, sizeof(vrt_kl));
	vrt_kl i;
	for(i = 0; i < count; i++) {
		p[i] = i;
	}
	return p;
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
		free(tmp);
	}
}

queue_kl* search_kl(edge_kl* gh, vrt_kl* p, vrt_kl N, edge_index_kl M) {
	int i;
	queue_kl* que = NULL;
	queue_kl* que_end = NULL;
	add_que_kl(&que, &(gh[0]));
	unite_dj_kl(p, gh[0].a, gh[0].b);
	que_end = que;
	for(i = 1; i < M; i++) {
		// printf("a:%hd b:%hd\n", p[gh[i].a], p[gh[i].b]);
		if(find_dj_kl(p, gh[i].a) != find_dj_kl(p, gh[i].b)) {
			// printf("a:%hd b:%hd\n", p[gh[i].a], p[gh[i].b]);
			add_que_kl(&que_end, &(gh[i]));
			unite_dj_kl(p, gh[i].a, gh[i].b);
			// printf("a:%hd b:%hd\n", p[gh[i].a], p[gh[i].b]);
		}
	}
	for(i = 1; i < N; i++) {
		// printf("search check %hd\n", i);
		if (find_dj_kl(p, i) != find_dj_kl(p, i - 1)) {
			// printf("fail\n");
			err_tsg = 6;
			free(que);
			return NULL;
		}
	}
	return que;
}

edge_kl* read_kl(FILE* in, vrt_kl* N, edge_index_kl* M) {
	vrt_kl i;
	edge_kl* gh;
	if(fscanf(in, "%hd%d", N, M) < 2) { //5 ошибка
		err_tsg = 5;
		return NULL;
	}
	else {
		if ((*N < minN) || (*N > maxN)) { //1 ошибка
			err_tsg = 1;
			return NULL;
		}
		if ((*M < minM) || (*M > maxM(*N))) { //2 ошибка
			err_tsg = 2;
			return NULL;
		}
		if(*N == 0) {
			err_tsg = 6;
			return NULL;
		}
	}
	gh = (edge_kl*)calloc(*M, sizeof(edge_kl));
	for (i = 0; i < *M; i++) {
		if(fscanf(in, "%hd%hd%d", &(gh[i].a), &(gh[i].b), &(gh[i].weight)) < 3) { //5 ошибка
			free(gh);
			err_tsg = 5;
			return NULL;
		}
		if((gh[i].a <= minN) || (gh[i].a > *N) || (gh[i].b <= minN) || (gh[i].b > *N)) { //3 ошибка
			free(gh);
			err_tsg = 3;
			return NULL;
		}
		if(gh[i].weight < 0) { // 4 ошибка
			free(gh);
			err_tsg = 4;
			return NULL;
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
	if (gh = read_kl(in, &N, &M)) {
		vrt_kl* p = create_dj_kl(N);
		queue_kl* que;
		// printf("read\n");
		qsort(gh, M, sizeof(edge_kl), (int(*) (const void*, const void*)) sort_edge_i_kl);
		// printf("qsort\n");
		if((que = search_kl(gh, p, N, M)) && M) {
			print_queue_kl(out, &que);
		}
		free(gh);
		free(p);
	}
	printf("%s", error_tsg());
}
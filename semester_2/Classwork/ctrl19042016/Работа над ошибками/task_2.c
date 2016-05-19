#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int var;
	struct _node* next;
}node;

typedef struct _graph{
	node* edges;
}graph;

node* push(node* head, int push) {
	if (head)
	{
		node* new = (node*)calloc(1, sizeof(node));
		new->var = push;
		new->next = head;
		head = new;
	}
	else {
		head = (node*)calloc(1, sizeof(node));
		head->var = push;
	}
	return head;
}

int pop(node** head)
{
	int tmp = -1;
	if (head && (*head)) {
		node* del;
		tmp = (*head)->var;
		del = *head;
		*head = (*head)->next;
		free(del);
	}
	return tmp;
}

int main (int argc, char **argv) {
	FILE *in = NULL, *out = NULL;
	if ((argc == 3) && (in = fopen(argv[1], "r")) && (out = fopen(argv[2], "w"))) {
		int N, i;
		int a, b;
		fscanf(in, "%d", &N);
		graph* gh = (graph*)calloc(N, sizeof(graph));
		while(fscanf(in, "%d %d", &a, &b) == 2) {
			gh[a - 1].edges = push(gh[a - 1].edges, b - 1);
		}
		fprintf(out, "%d\n", N);
		for (i = 0; i < N; i++) {
			if(gh[i].edges) {
				fprintf(out, "%d ", i + 1);
				while(gh[i].edges) {									
					fprintf(out, "%d ", pop(&(gh[i].edges)) + 1);
				}
				fprintf(out, "\n");
			}
		}
		free(gh);
	}
	if(in) fclose(in);
	if(out) fclose(out);
}
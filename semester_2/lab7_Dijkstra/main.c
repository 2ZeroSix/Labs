#include "dijkstra.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	dij_complete(stdin, stdout);
	fclose(in);
	fclose(out);
	return 0;
}
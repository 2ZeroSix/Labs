#define _CRT_SECURE_NO_WARNINGS
#include "dijkstra.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	dij_complete(in, out);
	fclose(in);
	fclose(out);
	return 0;
}
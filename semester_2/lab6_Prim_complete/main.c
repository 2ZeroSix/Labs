#include "Prim.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");
	pr_complete(in, out);
	fclose(in);
	fclose(out);
	return 0;
}

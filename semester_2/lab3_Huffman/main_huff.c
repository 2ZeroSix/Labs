#define _CRT_SECURE_NO_WARNINGS
#include "huff_func.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out", "wb");
	complete_compress_hf(in , out);
	fclose(in);
	fclose(out);
	return 0;
}
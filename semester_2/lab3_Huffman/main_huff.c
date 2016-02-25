#define _CRT_SECURE_NO_WARNINGS
#include "huff_func.h"

int main() {
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out", "wb");
	complete_compress_hf(in , out);
	fclose(in);
	fclose(out);
	in = fopen("out", "rb");
	out = fopen("test.txt", "w");
	complete_decompres_hf(in, out);
	fclose(in);
	fclose(out);
	return 0;
}
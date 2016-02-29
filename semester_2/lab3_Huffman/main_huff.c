#define _CRT_SECURE_NO_WARNINGS
#include "huff_func.h"

int main() {
	char c;
	long int shift = 3; // кол-во неважных байт в начале файла
	FILE* in = fopen("in.txt", "rb");
	FILE* out = fopen("out.txt", "wb");
	fread(&c, sizeof(char), 1, in);
	if (c == 'c') {
		complete_compress_hf(in, out, shift);
	}
	else if (c == 'd') {
		complete_decompres_hf(in, out, shift);
	}
	fclose(in);
	fclose(out);
	return 0;
}
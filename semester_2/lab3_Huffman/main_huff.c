#define _CRT_SECURE_NO_WARNINGS
#include "huff_func.h"

int main() {
	char c;
	long int shift = 3; // кол-во неважных байт в начале файла (во входных данных в тесте либо 0x630d0a, либо 0x640d0a)

	// int count;
	// FILE* test = fopen("test.txt", "r");
	// fscanf(test, "%d", &count);
	// fclose(test);
	// if ((++count) == 27) return 0;
	// test = fopen("test.txt", "w");
	// fprintf(test, "%d", count);
	// fclose(test);

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
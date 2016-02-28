#define _CRT_SECURE_NO_WARNINGS
#include "huff_func.h"
#include <string.h>
int main() {
	char c;
	if ((c = getchar()) == 'c') {
		getchar();
		complete_compress_hf(stdin, stdout);
	}
	else if (c == 'd') {
		getchar();
		complete_decompres_hf(stdin, stdout);
	}
	return 0;
}
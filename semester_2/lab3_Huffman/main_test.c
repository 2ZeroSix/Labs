#include <stdio.h>

int main() {
	FILE *in = fopen("test_code", "rb");
	unsigned char c;
	fread(&c, sizeof(unsigned char), 1, in);
	printf("%u : %c\n", c, c);
	fclose(in);
	return 0;
}
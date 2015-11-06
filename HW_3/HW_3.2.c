#include <stdio.h>

sortandprint(FILE *in, FILE *out1, FILE *out2, FILE *out3)

int open(FILE **in, FILE **out1, FILE **out2, FILE **out3)
{
 		return 0;
	if(fopen_s(out1, "out1.txt", "w") == NULL)
		return 0;
	if(fopen_s(out2, "out2.txt", "w") == NULL)
		return 0;
	if(fopen_s(out3, "out3.txt", "w") == NULL)
		return 0;
	return 1
}

void main()
{
	FILE* in, out1, out2, out3;
	if(open(&in, &out1, &out2, &out3))
	{
		sortandprint(in, out1, out2, out3);
	}
	else
	{
		printf("wrong files");
	}
}
#include <stdio.h>

void sortandprint(int *arr, FILE *out1, FILE *out2, FILE *out3)
{
	printf("sortandprint");

}
/*
open files with check
INPUT
- pointer on files
-- in
-- out1
-- out2
OUTPUT
-if completed
--<1>
-else
--<0>
*/
int open(FILE **in, FILE **out1, FILE **out2)
{
	printf("open");
	if(fopen_s(in, "in.txt", "r") == NULL)
		return 0;
	if(fopen_s(out1, "out1.txt", "w") == NULL)
		return 0;
	if(fopen_s(out2, "out2.txt", "w") == NULL)
		return 0;
	return 1;
}

int readin(FILE *in, void *arr[])
{
	char type[5];
	int sizearr;
	int i;
	fscanf(in, "%s", type, 3)
	fscanf(in, "%d", sizearr, sizeof(int));
	if (strcmp(type,"int") == 0)
	{
		*arr = (int*) malloc (sizearr*sizeof(int));
		for (i = 0; i < sizearr; i++)
		{
			fscanf(in, "%d", *arr[i])
		}
	}
	if (strcmp(type,"str") == 0)
	{
		int maxstrsize;
		arr = (char**) malloc (sizearr * sizeof(char*));
		fscanf(in, "%d", maxstrsize);
		for (i = 0; i < sizearr, i++)
		{
			arr[i] = (char*) malloc (maxstrsize*sizeof(char));
			fscanfs(in, "%s", arr[i]);
		}

	}
}
void main()
{
	void **arr;
	char *type;
	FILE* in, out1, out2;
	if(open(&in, &out1, &out2))
	{	
		readin(in, arr, type);
		sortandprint(arr, out1, out2);
	}
	else
	{
		printf("wrong files");
	}
}
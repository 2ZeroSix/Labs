#include <stdint.h>
#include <stdlib.h>
#define encode "-e"
#define decode "-d"
#define ignore "-i"
/*
input
-count of arguments <argc>
-arguments <**argv>
-pointer for input file <*out>
-for output file <*out>
-checker <check>
changes
-*in = pointer to input file
-*out = pointer to output file
-check[i - 1] = <not zero code> if argument[i] 	correct
output
-code <0> if arguments incorrect
-code <1> if arguments correct
*/
char checkmode(int argc, char **argv, FILE *in, FILE *out, char *check)
{
	/*counter*/
	short i = 1;
	/*checker*/
	int checkall = 1;
	if((argc == 3) || (argc == 4)
	{
		if (argc == 4)
		{
			if(strcmp(argv[i], ignore) == 0)
				check[i - 1] = 1;
			checkall *= check[i - 1];
		}
		i++;
		if (strcmp(argv[i], encode) == 0)
			check[i - 1] = 'e';
		checkall *= check[i - 1];
		if (strcmp(argv[i++], decode) == 0)
			check[i - 2] = 'd';
		checkall *= check[i - 2];
		if(in = fopen(argv[i++], "w")
			check[i - 2] = 1;
		checkall *= check[i - 2];
		out = fopen(argv[i])
	}
	if (checkall)
		return 1;
	return 0;
}

void output(char *check, int argc, char **argv)
{
	char outcode = {"wrong mode: ", "Wrong mode: ", "Wrong input file: ", }
	short i = 0;
	int checkall = 1;
	if (argc == 4)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], argv[i + 1]);
		checkall *= check[i++]
	}
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], argv[i + 1]);
	checkall *= check[i++]
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], argv[i + 1]);
	checkall *=check[i++];
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], argv[i + 1]);
	checkall *=check[i++];
	if (checkall)
		printf("%s\n", outcode[i])
	return;
}

void main(int argc, char **argv)
{
	char mode, check[4] = {0};
	FILE *in, *out;
	if(checkmode(argc, argv, in, out, check))
	{

	}
	output(check, argc, argv);
	return;
}
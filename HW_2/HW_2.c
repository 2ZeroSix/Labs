#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define encode "-e"
#define decode "-d"
#define ignore "-i"
/*
Text to Base64
Input
-input file <*in>
-output file <*out>
Changes
-print Base64 code in <*out>
*/
void encoder(FILE *in, FILE *out)
{
	char c[3];
	// char b64[4];
	while (c[0] = getc(in) != EOF)
	{
		printf("%c", c[0] >> 2);
		if ((c[1] = getc(in)) == EOF)
		{
			printf("%c", (c[0] << 4) | 0x3f);
			return;
		}
		printf("%c", ((c[0] << 4) | (c[1] >> 4)) | 0x3f);
		if ((c[2] = getc(in)) == EOF)
		{
			printf("%c", (c[1] << 2) | 0x3f);
			return;
		}
		printf("%c", ((c[1] << 2) | c[2] >> 6) | 0x3f);
		printf("%c", (c[2]) | 0x3f);
		// b64[0] = c[0] >> 2
		// b64[1] = ((c[0] << 4) | (c[1] >> 4)) | 0x3f;
		// b64[2] = ((c[1] << 2) | c[2] >> 6) | 0x3f;
		// b64[3] = (c[2]) | 0x3f;
	}
	return;
}
/*
Base64 to text
Input
-input file  <*in>
-output file <*out>
-ignore mode <im>
Changes
-print text in <*out>
Output
-code <1> if completed
-code <0> if wrong value in file
*/
char decoder(FILE *in, FILE *out, int im)
{
	short i;
	char b64[4], c[3];
	while ((b64[0] = getc(in)) != EOF)
	{
		for (i = 1; i < 4; i++)
			if (((b64[i] = getc(in)) > 0x3f) || (b64[i] < 0))
			{
				if (im)
				{
					while (((b64[i] > 0x3f) || (b64[i] < 0)) && (b64[i] != EOF));
				}
				else
				{
					return 0;
				}
			}
		c[0] = (b64[0] << 2) | (b64[1] >> 4);
		c[1] = (b64[1] << 4) | (b64[1] >> 2);
		c[2] = (b64[2] << 6) | (b64[3]);
	}
	return 1;
}
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
char checkmode(int argc, char **argv, FILE **in, FILE **out, int *check)
{
	/*counter*/
	short i = 1;
	/*checker*/
	int checkall = 1;
	if ((argc == 3) || (argc == 4))
	{
		if (argc == 4)
		{
			if (strcmp(argv[i], ignore) == 0)
				check[i - 1] = 1;
			checkall *= check[i - 1];
		}
		i++;
		if (strcmp(argv[i], encode) == 0)
			check[i - 1] = 'e';
		if (strcmp(argv[i++], decode) == 0)
			check[i - 2] = 'd';
		checkall *= check[i - 2];
		if (fopen_s(in, argv[i++], "r") == NULL)
			check[i - 2] = 1;
		checkall *= check[i - 2];
		if (fopen_s(out, argv[i], "w") == NULL)
			check[i - 1] = 1;
		checkall *= check[i - 1];
	}
	else
	{
		return 0;
	}
	if (checkall != 0)
		return 1;
	return 0;
}

/*
Print outcode
Input
-checks <*check>
-count of arguments <argc>
-argumentts <**argv>
*/
void output(int *check, int argc, char **argv)
{
	char *outcode[5] = { "Wrong ignore mode: ", "Wrong decode/encode mode: ", "Wrong input file: ", "COMPLETEED\nResult in output file", "ERROR\nInterface: <ignore mode> <decode/encode mode> <input file> <output file>\nIgnore modes:\n- <-i> - ignore nonBase64 symbols while decoding\n- empty - not ignore nonBase64 symbols\nDecode/encode modes:\n- <-d> - decode\n- <-e> - encode\nInput file\nOutput file\n" };
	short i = 0;
	int checkall = 1;
	if (argc == 4)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], argv[i + 1]);
		checkall *= check[i++];
	}
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], argv[i + 1]);
	checkall *= check[i++];
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], argv[i + 1]);
	checkall *= check[i++];
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], argv[i + 1]);
	checkall *= check[i++];
	if (checkall)
	{
		printf("%s\n", outcode[i]);
	}
	else
	{
		printf("%s\n", outcode[i + 1]);
	}
	return;
}

void main(int argc, char **argv)
{
	int check[4] = { 0 };
	FILE *in, *out;
	if (checkmode(argc, argv, &in, &out, check))
	{
		if (check[2] == 'e')
		{
			encoder(in, out);
		}
		else
		{
			decoder(in, out, check[1]);
		}
	}
	output(check, argc, argv);
	return;
}
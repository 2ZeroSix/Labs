#include "ende64.h"

char b64sym(char sym)
{
	if (sym <= 25)
	{
		sym += 'A';
	}
	else
	{
		if (sym <= 51)
		{
			sym += 'a';
		}
		else
		{
			if (sym <= 61)
			{
				sym += '0';
			}
			else
			{
				if (sym = 62)
				{
					sym = '+';
				}
				else
				{
					sym = '-';
				}
			}
		}
	}
	return sym;
}
void encoder(FILE *in, FILE *out)
{
	char c[3];
	while (c[0] = getc(in) != EOF)
	{
		putc(b64sym(c[0] >> 2), out);
		if ((c[1] = getc(in)) == EOF)
		{

			putc(b64sym((c[0] << 4) & 0x3f), out);
			putc('=', out);
			putc('=', out);
			return;
		}
		putc(b64sym(((c[0] << 4) | (c[1] >> 4)) & 0x3f), out);
		if ((c[2] = getc(in)) == EOF)
		{
			putc(b64sym((c[1] << 2) & 0x3f), out);
			putc('=', out);
			return;
		}
		putc(b64sym(((c[1] << 2) | (c[2] >> 6)) & 0x3f), out);
		putc(b64sym((c[2]) & 0x3f), out);
	}
	return;
}

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

char checkmode(int argc, char *argv[], FILE **in, FILE **out, int *check)
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
		if (fopen_s(in, argv[i++], "r") == 0)
			check[i - 2] = 1;
		checkall *= check[i - 2];
		if (fopen_s(out, argv[i], "w") == 0)
			check[i - 1] = 1;
		checkall *= check[i - 1];
	}
	else
	{
		return 0;
	}

	return checkall;
}

void output(int *check, int argc, char *argv[])
{
	char *outcode[5] = { "Wrong ignore mode: ", "Wrong decode/encode mode: ", "Wrong input file: ", "COMPLETEED\nResult in output file", "ERROR\nInterface: <ignore mode> <decode/encode mode> <input file> <output file>\nIgnore modes:\n- <-i> - ignore nonBase64 symbols while decoding\n- empty - not ignore nonBase64 symbols\nDecode/encode modes:\n- <-d> - decode\n- <-e> - encode\nInput file\nOutput file\n" };
	short i = 0;
	int checkall = 1;
	if (argc == 4)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], (argc > 0) ? argv[i + 1] : "");
		checkall *= check[i++];
	}
	i++;
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], (argc > 1) ? argv[i + 1] : "");
	checkall *= check[i++];
	if (check[i] == 0)
		printf("%s %s\n", outcode[i], (argc > 2) ? argv[i + 1] : "");
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
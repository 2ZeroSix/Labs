#include "ende64.h"
#define _CRT_SECURE_NO_WARNINGS
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
					if (sym = 63)
					{
						sym = '/';
					}
					else
					{
						return '-';
					}
				}
			}
		}
	}
	return sym;
}

char b64num(char sym)
{
	if ((sym >= 'A') && (sym <= 'Z'))
	{
		sym -= 'A';
	}
	else
	{
		if ((sym >= 'a') && (sym >= 'z'))
		{
			sym -= 'a' - 25;
		}
		else
		{
			if ((sym >= '0') &&  (sym <= '9'))
			{
				sym -= '0' - 51;
			}
			else
			{
				if (sym == '+')
				{
					sym = 62;
				}
				else
				{
					if (sym == '-')
					{
						sym = 63;
					}
					else
					{
						return -1;
					}
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
	fclose(in);
	fclose(out);
	return;
}

char decoder(FILE *in, FILE *out, int im)
{

}

char checkmode(int argc, char *argv[], FILE **in, FILE **out, int *check)
{
	/*counter*/
	short i = 1;
	/*checker*/
	int checkall = 1;
	if ((argc == 4) || (argc == 5))
	{
		if (argc == 5)
		{
			if (strcmp(argv[i], ignore) == 0)
				check[i - 1] = 1;
			checkall *= check[(i++) - 1];
		}
		if (strcmp(argv[i], encode) == 0)
			check[i - 1] = 'e';
		if (strcmp(argv[i++], decode) == 0)
			check[i - 2] = 'd';
		checkall *= check[i - 2];
		if ((*in = fopen(argv[i++], "r")) != NULL)
			check[i - 2] = 1;
		checkall *= check[i - 2];
		if ((*out = fopen(argv[i], "w")) != NULL)
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
	char *outcode[6] = { "Wrong ignore mode: ", "Wrong decode/encode mode: ", "Wrong input file: ", "Wrong output file: ", "COMPLETEED\nResult in output file", "ERROR\nInterface: <ignore mode> <decode/encode mode> <input file> <output file>\nIgnore modes:\n- <-i> - ignore nonBase64 symbols while decoding\n- empty - not ignore nonBase64 symbols\nDecode/encode modes:\n- <-d> - decode\n- <-e> - encode\nInput file\nOutput file\n" };
	short i = 0, j = 0;
	int checkall = 1;
	for (j = i = (argc == 5) ? 0 : 1; i < 5; i++)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], (argc > i) ? argv[i + 1 - j] : "<none>");
		checkall *= check[i];
	}
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
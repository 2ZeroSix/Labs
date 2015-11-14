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
				if (sym == 62)
				{
					sym = '+';
				}
				else
				{
					if (sym == 63)
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
	printf("%c", sym);
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
					if (sym == '/')
					{
						sym = 63;
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

void encoder(FILE *in, FILE *out)
{
	char c[3], b64[4];
	while ((c[0] = getc(in)) != EOF)
	{
		b64[0] = b64sym((c[0] >> 2) & 0x3f);
		putc(b64[0], in);
		if ((c[1] = getc(in)) == EOF)
		{
			b64[1] = b64sym((c[0] << 4) & 0x3f);
			putc(b64[1], in);
			putc('=', in);
			putc('=', in);
			return;
		}
		b64[1] = b64sym(((c[0] << 4) | (c[1] >> 4)) & 0x3f);
		putc(b64[1], in);
		if ((c[2] = getc(in)) == EOF)
		{
			b64[2] = b64sym((c[1] << 2) & 0x3f);
			putc(b64[2], in);
			putc('=', in);
			return;
		}
		b64[2] = b64sym(((c[1] << 2) | (c[2] >> 6)) & 0x3f);
		b64[3] = b64sym(c[2] & 0x3f);
		putc(b64[2], in);
		putc(b64[3], in);
	}
	return;
}

char decoder(FILE *in, FILE *out, int im)
{
	int i, count = 4;
	char c[3], b64[4];
	while ((b64[0] = getc(in)) != EOF)
	{
		for (i = 0; i < 4; i++)
		{
		if (i > 0)
			b64[i] = getc(in);
		if ((b64[i] == EOF) || ((i < 2) && (b64[i] == '=')))
			return 0;
		if (b63[i] != '=')
		{
			if (im == 1)
			{
				while(b64[i] == '-')
					b64[i] = getc(in);
			}
			if (b64[i] == '-')
				return 0;
		}
		else
		{
			if (i == 3)
				count = 1;
			if (i == 4)
			{
				if (b64[i - 1] == '=')
				{
					count = 2;
				}
				else
				{
					return 0;
				}
			}
		}
		}
		c[0] = ((b64[0] << 2) & (b64[1] >> 4);
		c[1] = ((b64[1] << 4) & (b64[2] >> 2);
		c[2] = ((b64[2] << 6) & (b64[2]));
	}
}

int checkmode(int argc, char *argv[], FILE **in, FILE **out, int *check)
{
	int checkall = 1, i = 0, j = 0;
	if(argc == 5)
	{
		j = 1;
		if (strcmp(argv[i + j], "-i")
			check[i] = 1;
		checkall *= check[i];
	}
	i++;
	if(argc > i)
	{
		if (strcmp(argv[i + j], "-e"))
			check[i] = 'e';
		if (strcmp(argv[i + j], "-d"))
			check[i] = 'd';
	}
	checkall *= check[i];
	i++;
	if (argc > i)
	{
		if ((*in = fopen(argv[i + j], "r")) != NULL)
			check[i] = 1;
	}
	checkall *= check[i];
	i++;
	if (argc > i)
	{
		if ((*out = fopen(argv[i + j], "w")) != NULL)
			check[i] = 1;
	}
	checkall *= check[i];
	if ((argc != 4) && (argc != 5))
	{
		checkall = 0;
	}
	return checkall;
}

void output(int *check, int argc, char *argv[])
{
	char outcode[] = {"wrong ignore mode:", "wrong encode/decode mode:", "wrong input file:", "wrong output file:", "wrong count of args", "COMPLETEED\nResult in output file", "ERROR\nInterface: <ignore mode> <decode/encode mode> <input file> <output file>\nIgnore modes:\n- <-i> - ignore nonBase64 symbols while decoding\n- empty - not ignore nonBase64 symbols\nDecode/encode modes:\n- <-d> - decode\n- <-e> - encode\nInput file\nOutput file\n"}
	int i = (argc == 5) ? 0 : 1, j = (argc == 5) ? 1 : 0, checkall = 1;
	for (i; i < sizecheck; i++)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], (argc > (i + j)) ? argv[i + j] : "<none>");
		checkall = check[i];
	}
	if ((argc != 4) && (argc != 5))
		printf("%s %s\n", outcode[i], argc);
	i++;
	if (checkall)
	{
		outcode[i];
	}
	else
	{
		outcode[i + 1];
	}
	return;
}
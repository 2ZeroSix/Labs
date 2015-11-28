#include "ende64.h"
unsigned char b64sym(unsigned char sym)
{
	if (sym <= 25)
	{
		sym += 'A';
	}
	else
	{
		if (sym <= 51)
		{
			sym += 'a' - 26;
		}
		else
		{
			if (sym <= 61)
			{
				sym += '0' - 52;
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
						sym = 64;
					}
				}
			}
		}
	}
	return sym;
}

void encoder(FILE *in, FILE *out)
{
	unsigned char c[3], b64[5] = { 0 }, count, i;
	printf("encoder\n");
	while (count = fread(c, sizeof(char), 3, in))
	{
		for(i = count; i < 3; i++)
			c[i] = 0;
		b64[0] = b64sym((c[0] >> 2) & 0x3f);
		b64[1] = b64sym(((c[0] << 4) | (c[1] >> 4)) & 0x3f);
		b64[2] = b64sym(((c[1] << 2) | (c[2] >> 6)) & 0x3f);
		b64[3] = b64sym(c[2] & 0x3f);
		for (i = count + 1; i < 4; i++)
			b64[i] = '=';
		fprintf(out, "%s", b64);
	}
	return;
}

unsigned char b64num(unsigned char sym)
{
	if ((sym >= 'A') && (sym <= 'Z'))
	{
		sym -= 'A';
	}
	else
	{
		if ((sym >= 'a') && (sym <= 'z'))
		{
			sym = sym - 'a' + 26;
		}
		else
		{
			if ((sym >= '0') &&  (sym <= '9'))
			{
				sym = sym - '0' + 52;
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
						sym = 64;
					}
				}
			}
		}
	}
	return sym;
}

char decoder(FILE *in, FILE *out, int im)
{
	unsigned char c[3], b64[4], i, count = 3;
	int j = 0;
	while(((signed char)(b64[0] = getc(in))) != EOF)
	{
		for (i = 0; i < 4; i++)
		{
			if (i > 0)
				b64[i] = getc(in);
			if((b64[i] != '=') && (count == 3))
			{
				while((b64num(b64[i]) > 0x3f) && (im == 1) && ((signed char)b64[i] != EOF))
					{
						// printf("%d\n", b64[i]);
						b64[i] = getc(in);
					}
				if (b64num(b64[i]) > 0x3f)
				{
					printf("%s, %d, %d\n", ((signed char)b64[i] == EOF) ? "EOF" : "0x3f", (signed char)b64[i], i + j);
					return 0;
				}
				b64[i] = b64num(b64[i]);
			}
			else if ((i > 1) && (b64[i] == '='))
			{
				count = (count == 3) ? i - 1 : 1;
				b64[i] = 0;
			}
			else
			{
				printf("wrong2\n");
				return 0;
			}
		}
		if (count < 3)
			if (getc(in) != EOF)
			{
				printf("wrong3\n");
				return 0;
			}
		c[0] = (b64[0] << 2) | (b64[1] >> 4);
		c[1] = (b64[1] << 4) | (b64[2] >> 2);
		c[2] = (b64[2] << 6) | (b64[3]);
		fwrite(c, sizeof(char), count, out);
		j+=4;
	}
	printf("decoded\n");
	return 1;
}

int checkmode(int argc, char *argv[], FILE **in, FILE **out, int *check)
{
	int checkall = ((argc != 5) && (argc != 4)) ? 0 : 1, i = 1;
	if (argc == 5)
		{
		if (strcmp(argv[i], "-i") == 0)
			check[0] = 1;
		checkall *= check[0];
		i++;
		}
	if (argc > i)
	{
		if (strcmp(argv[i], "-e") == 0)
			check[4] = check[1] = 1;
		if (strcmp(argv[i], "-d") == 0)
			check[1] = 2;
		i++;
	}
	checkall *= check[1];
	if (argc > i)
	{
		if (*in = fopen(argv[i], (check[1] == 1) ? "rb" : "r"))
			check[2] = 1;
		i++;
	}
	checkall *= check[2];
	if (argc > i)
	{
		if (*out = fopen(argv[i], (check[1] == 1) ? "w" : "wb"))
			check[3] = 1;
	}
	checkall *= check[3];
	return checkall;
}

void output(int *check, int argc, char *argv[])
{
	char *outcode[8] = {"wrong ignore mode:", "wrong encode/decode mode:", "wrong input file:", "wrong output file:", "wrong symbols in input file", "wrong count of args", "COMPLETE\nResult in output file", "ERROR\nInterface: <ignore mode> <decode/encode mode> <input file> <output file>\nIgnore modes:\n- <-i> - ignore nonBase64 symbols while decoding\n- empty - not ignore nonBase64 symbols\nDecode/encode modes:\n- <-d> - decode\n- <-e> - encode\nInput file\nOutput file\n"};
	int i = (argc == 5) ? 0 : 1, j = (argc == 5) ? 1 : 0, checkall = 1;
	for (i; i < sizecheck; i++)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], (argc > (i + j)) ? argv[i + j] : "<none>");
		checkall *= check[i];
	}
	if ((argc != 4) && (argc != 5))
		printf("%s %d\n", outcode[i], argc);
	i++;
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
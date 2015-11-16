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
	printf("encoder\n");
	char c[3], b64[4];
	while (fread(&c[0], 1, 1, in) == 1)
	{
		b64[0] = b64sym((c[0] >> 2) & 0x3f);
		putc(b64[0], out);
		if (fread(&c[1], 1, 1, in) == 1)
		{
			b64[1] = b64sym((c[0] << 4) & 0x3f);
			putc(b64[1], out);
			putc('=', out);
			putc('=', out);
			return;
		}
		b64[1] = b64sym(((c[0] << 4) | (c[1] >> 4)) & 0x3f);
		putc(b64[1], out);
		if (fread(&c[2], 1, 1, in) == 1);
		{
			b64[2] = b64sym((c[1] << 2) & 0x3f);
			putc(b64[2], out);
			putc('=', out);
			return;
		}
		b64[2] = b64sym(((c[1] << 2) | (c[2] >> 6)) & 0x3f);
		b64[3] = b64sym(c[2] & 0x3f);
		putc(b64[2], out);
		putc(b64[3], out);
		printf("%c %c %c %c\n", b64[0], b64[1], b64[2], b64[3]);
	}
	return;
}

char b64num(char sym)
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
						return '-';
					}
				}
			}
		}
	}
	return sym;
}

char decoder(FILE *in, FILE *out, int im)
{
	int i, count;
	char c[3], b64[4];
	while ((b64[0] = getc(in)) != EOF)
	{
		count = 3;
		for (i = 0; i < 4; i++)
		{
			if (i > 0)
				b64[i] = getc(in);
			if (b64[i] == EOF)
				return 0;
			if (b64[i] != '=')
			{
				if (count == 1)
					return 0;
				if (im == 1)
				{
					while(b64num(b64[i]) == '-')
						b64[i] = getc(in);
				}
				if ((b64[i] = b64num(b64[i])) == '-')
					return 0;
			}
			else
			{
				if (i < 2)
					return 0;
				if (i == 2)
					count = 1;
				if (i == 3)
				{
					count = 2;
				}
				b64[i] = 0;
			}
		}
		c[0] = (b64[0] << 2) | (b64[1] >> 4);
		putc(c[0], out);
		if (count >1)
		{
			c[1] = (b64[1] << 4) | (b64[2] >> 2);
			putc(c[1], out);
		}
		if (count > 2)
		{
			c[2] = (b64[2] << 6) | (b64[3]);
			putc(c[2], out);
		}
		printf("%c %c %c\n", c[0], c[1], c[2]);
	}
}

int checkmode(int argc, char *argv[], FILE **in, FILE **out, int *check)
{
	int checkall = 1, i = 1, j = 0;
	if (argc > 1)
	{
		if ((strlen(argv[1]) == 2) && (*argv[1] == '-'))
		{
			switch(*(argv[1] + 1))
			{
				case 'i':
					check[0] = '1';
					if(((argc > 2) ? *(argv[2] + 1) : 0 )  == 'd')
						check[1] = 'd';
					i = 3;
					break;
				case 'e':
					check[1] = 'e';
					i = 2;
					break;
				case 'd':
					check[1] = 'd';
					i = 2;
					break;
				default:
					checkall = 0;
					break;
			}
			if ((i > 1) && (argc >= i))
			{
				switch(check[1])
				{
					case 'e':
						if((*in = fopen(argv[i], "rb")) != NULL)
							check[2] = 1;
						if(argc > i)
							if((*out = fopen(argv[i + 1], "w")) != NULL)
								check[3] = 1;
						break;
					case 'd':
						if((*in = fopen(argv[i], "r")) != NULL)
							check[2] = 1;
						if(argc > i)
							if((*out = fopen(argv[i + 1], "wb")) != NULL)
								check[3] = 1;
						break;
					default:
						break;
				}
			}
		}
	}
	if ((argc != 5) && (argc != 4))
		checkall = 0;
	return checkall;
}

void output(int *check, int argc, char *argv[])
{
	char *outcode[7] = {"wrong ignore mode:", "wrong encode/decode mode:", "wrong input file:", "wrong output file:", "wrong count of args", "COMPLETEED\nResult in output file", "ERROR\nInterface: <ignore mode> <decode/encode mode> <input file> <output file>\nIgnore modes:\n- <-i> - ignore nonBase64 symbols while decoding\n- empty - not ignore nonBase64 symbols\nDecode/encode modes:\n- <-d> - decode\n- <-e> - encode\nInput file\nOutput file\n"};
	int i = (argc == 5) ? 0 : 1, j = (argc == 5) ? 1 : 0, checkall = 1;
	for (i; i < sizecheck; i++)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], (argc > (i + j)) ? argv[i + j] : "<none>");
		checkall = check[i];
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
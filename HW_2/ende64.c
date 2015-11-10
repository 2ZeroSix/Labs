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
	printf("encode");
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
	
}

void output(int *check, int argc, char *argv[])
{

}
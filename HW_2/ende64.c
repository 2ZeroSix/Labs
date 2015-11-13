#include "ende64.h"
char b64sym(char sym)
{
	printf("\n%d\n", sym);

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
	char c[3];
	printf("encode\n");
	while (c[0] = getc(in) != EOF)
	{
		
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
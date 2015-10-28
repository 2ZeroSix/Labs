#include <stdio.h>
#include "cmdcalc.h"
#include "funsym.h"

static char *outcode[] = {"Syntax error", "Division by zero"};
/*
Read with check
INPUT
- massive for exception <*exep>
OUTPUT
- if syntax error
-- code <0>
- if completed
-- code <1>
*/
char readexep(short *ecxep, long long *args)
{
	// counters
	short i, j = 0, st = 0;
	// buffer
	char c;
	// stack
	char stack[1000];
	while ((c = getchar()) != EOF)
	{
		if ((i > 999) || (stack > 999))
			return 0;
		if ((c >= '0') && (c <= '9'))
		{
			if (j < 500)
			{
				do
				{
					args[j] = args[j] * 10 + c - '0';	
				} while(((c = getchar()) >= '0') && (c <= '9'));
				excep[i++] = j;
				j++;
			}
			else
			{
				reurn 0;
			}
		}
		else
		{
			switch (c)
			{
				case '+':
					stack[k++] = plus;
					break;
				case '-':
					stack[k++] = minus;
					break;
				case '*'
					stack[k++] = mult;
					break;
				case '/':
					stack[k++] = split;
					break;
				case '(':
					stack[k++] = obra;
					break;
				default:
					if(c == ')')
					{
						while(stack[k] != obra
						{
							excep[i++] = stack[k--];
							if(k < 0)
								return 0;
						}
						k--;
					}
					else
					{
						return 0;
					}	
			}
		}
	}
	while(K >= 0)
	{
		if((i > 999) || (stack[k] == obra)
			return 0;
		excep[i++] = stack[k--];
	} 
	excep[i] = exend;
	return 1;
}
/*
Print result of work
INPUT
- output code <checker>
- result of calculation	<result>
CHANGES
- if checker == 2 
--print result of calculation
- else
--print code of error
---<1> - "division by zero"
---<0> - "syntax error"
*/
void output(char checker, long long result)
{
	if (checker < 2)
	{
		printf("%s", outcode[checker]);
	}
	else
	{
		printf("%lld", result);
	}
	return;
}
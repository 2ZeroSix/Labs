#include "calc.h"
#include <stdio.h>

char fullcalc(short *excep, long long *args)
{
	short i, j = 0, stack[500];
	for (i = 0; excep[i] != exend; i++)
	{
		if (excep[i] < 500)
		{
			stack[j++] = excep[i];
		}
		else
		{
			switch (excep[i])
			{
			case plus:
				args[stack[j - 2]] += args[stack[j - 1]];
				j--;
				break;
			case minus:
				args[stack[j - 2]] -= args[stack[j - 1]];
				j--;
				break;
			case mult:
				args[stack[j - 2]] *= args[stack[j - 1]];
				j--;
				break;
			case split:
				if (args[stack[j - 1]] == 0)
					return 1;
				args[stack[j - 2]] /= args[stack[j - 1]];
				j--;
				break;
			}
		}
	}
	return 2;
}


char readexcep(short *excep, long long *args)
{
	// counters
	short i = 0, j = 0, st = 0, k = 0;
	// buffer
	char c, last = 0;
	// stack
	short stack[1000];
	while (((c = getchar()) != EOF) && (c != '\n'))
	{
		if (((c == ')') && (last == '(')) || ((c == '+') || (c == '-') || (c == '*') || (c == '/')) && ((last == '+') || (last == '-') || (last == '*') || (last == '/')))
			return 0;
		if ((i > 999) || (k > 999))
			return 0;
		if ((c >= '0') && (c <= '9'))
		{
			if (j < 500)
			{
				do
				{
					args[j] = args[j] * 10 + c - '0';
				} while (((c = getchar()) >= '0') && (c <= '9'));
				excep[i++] = j;
				j++;
			}
			else
			{
				return 0;
			}
		}
		if ((c != EOF) && (c != '\n'))
		{
			switch (c)
			{
			case '+':
				if ((stack[k - 1] == split) || (stack[k - 1] == mult))
				{
					excep[i++] = stack[--k];
				}
				stack[k++] = plus;
				break;
			case '-':
				if ((stack[k - 1] == split) || (stack[k - 1] == mult) || (stack[k - 1] == minus))
				{
					excep[i++] = stack[--k];
				}
				stack[k++] = minus;
				break;
			case '*':
				if (stack[k - 1] == mult)
				{
					excep[i++] = stack[--k];
				}
				stack[k++] = mult;
				break;
			case '/':
				if ((stack[k - 1] == split) || (stack[k - 1] == mult))
				{
					excep[i++] = stack[--k];
				}
				stack[k++] = split;
				break;
			case '(':
				stack[k++] = obra;
				break;
			default:
				if (c == ')')
				{
					k--;
					while (stack[k] != obra)
					{
						excep[i++] = stack[k--];
						if (k < 0)
							return 0;
					}
				}
				else
				{
					return 0;
				}
			}
		}
		last = c;
	}
	if ((last == '+') || (last == '-') || (last == '*') || (last == '/') || (j == 0))
		return 0;
	k--;
	while (k >= 0)
	{
		if ((i > 999) || (stack[k] == obra))
			return 0;
		excep[i++] = stack[k--];
	}
	excep[i] = exend;
	return 1;
}

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
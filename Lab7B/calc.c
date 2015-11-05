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
				j -= 2;
				break;
			case minus:
				args[stack[j - 2]] -= args[stack[j - 1]];
				j -= 2;
				break;
			case mult:
				args[stack[j - 2]] *= args[stack[j -1]];
				j -= 2;
				break;
			case split:
				if (args[stack[j - 1]] == 0)
					return 1;
				args[stack[j - 2]] /= args[stack[j -1]];
				j -= 2;
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
	char c;
	// stack
	short stack[1000];
	while (((c = getchar()) != EOF) && (c != '\n'))
	{
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
				stack[k++] = plus;
				break;
			case '-':
				stack[k++] = minus;
				break;
			case '*':
				stack[k++] = mult;
				break;
			case '/':
				stack[k++] = split;
				break;
			case '(':
				stack[k++] = obra;
				break;
			default:
				if (c == ')')
				{
					if (stack[k - 1] == obra)
						return 0;
					while (stack[k] != obra)
					{
						excep[i++] = stack[k--];
						if (k < 0)
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
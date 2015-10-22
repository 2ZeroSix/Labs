#include <stdio.h>
#include <stdlib.h>
#define codez printf("division by zero");
#define codes printf("syntax error");
/*closing brackets*/
#define bracc 500
/*opening brackets*/
#define braco 501
#define plus 502
#define minus 503
#define mult 504
#define split 505
#define empty -1
/*
Calculate one expression
input
-expression <*toc>
-arguments <*arg>
-position of expression <pexp>
changes
-toc[position of arg2] = empty, ptoc[pexp] = empty
-arg[arg1 position] = result of calc
output
-code <0> if division by zero
-code <1> if completed
*/
char expcalc(short *toc, long long *arg, short pexp)
{
	/*positions of args*/
	short arg1pos = pexp - 1, arg2pos = pexp + 1;
	while (toc[arg1pos] == empty)
		arg1pos--;
	while(toc[arg2pos] == empty)
		arg2pos++;
	switch (toc[pexp])
	{
		case plus:
			arg[toc[arg1pos]] += arg[toc[arg2pos]];
			break;
		case minus:
			arg[toc[arg1pos]] -= arg[toc[arg2pos]];
			break;
		case mult:
			arg[toc[arg1pos]] *= arg[toc[arg2pos]];
			break;
		case split:
			if(arg[toc[arg2pos]] == 0)
				return 0;
			arg[toc[arg1pos]] /= arg[toc[arg2pos]];
			break;
	}
	toc[pexp] = empty;
	toc[arg2pos] = empty;
	return 1;
}
/*
Calculate expression in brackets
input
-expression <*toc>
-arguments <*arg>
-opening bracket position
-closing bracket position
changes
-toc[bop]=...toc[bcp] = empty
-arg[first in brackets] = result of calc
output
-code <0> if division by zero
-code <1> if completed
*/
char brcalc(short *toc, long long *arg, short bop, short bcp)
{
	/*counter*/
	short i;

	for (i = bop + 1; i < bcp - 1; i++)
	{
		if ((toc[i] == mult) || (toc[i] == split))
		{
			if(expcalc(toc, arg, i) == 0)
				return 0;
		}
	}
	for (i = bop + 1; i < bcp - 1; i++)
	{
		if ((toc[i] == plus) || (toc[i] == minus))
		{
			if (expcalc(toc, arg, i) == 0)
				return 0;
		}
	}
	toc[bop] = empty;
	toc[bcp] = empty;
	return 1;
}
/*
main calculating function
input
-expression <*toc>
-arguments <*arg>
-expression length <length>
-variable for expression result <*result>
changes
-fill <result>
output
-code <1> if division by zero
-code <2> if completed
*/
char fullcalc(short *toc, long long *arg, short length, long long *result)
{
	/*counters*/
	short i, j = 0;
	/*every opening brackets positions*/
	short bop[499];
	/*last closing bracket position*/
	for (i = 0; i < length; i++)
	{
		if (toc[i] == braco)
			bop[j++] = i;
		if (toc[i] == bracc)
		{
			if (brcalc(toc, arg, bop[--j], i) == 0)
				return 1;
		}
	}
	*result = arg[0];
	return 2;
}
/*
Check symbol
input
-expression <*toc>
-expression arguments <*arg>
-count of opening brackets <*bo>
-count of closing brackets <*bc>
-counters
--<*i>
--<*j>
-"in out" variable <*k>
changes
-all to actual values
return
-code <0> if syntax error
-code <1> if completed
*/
char chksmb(char c, short *toc, long long *arg, short *bo, short *bc, short *i, short *j, char *k)
{
	if ((c >= '0') && (c <= '9'))
	{	
		*k = 1;
		arg[*j] = arg[*j] * 10 + c - '0'; 
	}
	else
	{
		if (*k == 1)
		{
			toc[*i] = *j;
			*k = 0;
			(*i)++;
			(*j)++;
		}
		switch (c)
		{
			case '(':
				toc[*i] = braco;
				(*bo)++;
				break;
			case ')':
				toc[*i] = bracc;
				(*bc)++;
				break;
			case '+':
				toc[*i] = plus;
				break;
			case '-':
				toc[*i] = minus;
				break;
			case '*':
				toc[*i] = mult;
				break;
			case '/':
				toc[*i] = split;
				break;
			default:
				return 0;
				break;
		}
		if ((*bc > *bo) || ((toc[*i - 1] == bracc) && (toc[*i] == braco)) || ((toc[*i - 1] == braco) && (toc[*i] == bracc)) || ((toc[*i - 1] == braco) && ((toc[*i] == plus) || (toc[*i] == split) || (toc[*i] == mult) || (toc[*i] == minus))) || ((toc[*i] == bracc) && ((toc[*i - 1] == plus) || (toc[*i - 1] == split) || (toc[*i - 1] == mult) || (toc[*i - 1] == minus))) || (((toc[*i] == plus) || (toc[*i] == minus) ||(toc[*i] == mult) || (toc[*i] == split)) && ((toc[*i - 1] == plus) || (toc[*i - 1] == minus) ||(toc[*i - 1] == mult) || (toc[*i - 1] == split))))
			return 0;
		(*i)++;
	}
	return 1;
}
/*
read input
input
-massive for expression <*toc>
-variable for expression arguments <*arg>
changes
-fill <*toc>
-fill <*arg>
output
-length of <*toc> if completed
-code <0> if syntax error
*/
short scancalc(short *toc, long long *arg)
{
	/*temp*/
	char c, k = 0;
	/*counters*/
	short i = 0, j = 0;
	/*
	-count of opening brackets
	-count of closing brackets
	*/
	short bo = 0, bc = 0;
	toc[i++] = braco;
	while (((c = getchar()) != EOF) && (c != '\n') && (i < 1001))
	{
		if((chksmb(c, toc, arg, &bo, &bc, &i, &j, &k)) == 0)
			return 0;
	}
	if ((c != EOF) && (c != '\n'))
		return 0;
	chksmb(c, toc, arg, &bo, &bc, &i, &j, &k);
	if ((bo != bc) || (toc[i - 1] > bracc))
		return 0;
	toc[i++] = bracc;
	return i;
}
/*
print output message
input
-output code <codecalc>
-expression result <result>
*/
void output(char codecalc, long long result)
{
		switch(codecalc)
	{
		case 0:
			codes
			break;
		case 1:
			codez
			break;
		case 2:
			printf("%lld",result);
			break;
	}
	return;
}

void main()
{
	/*output code*/
	char codecalc = 0;
	/*expression*/
	short toc[1002];
	/*arguments*/
	long long arg[500] = {0};
	/*expression length*/
	short length;
	/*result of calculating*/
	long long result;
	if((length = scancalc(toc, arg)) > 0)
	{
		codecalc = fullcalc(toc, arg, length, &result);
	}
	output(codecalc, result);
	return;
}
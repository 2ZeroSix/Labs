#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define codez printf("division by zero");
#define codes printf("syntax error");
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
-code 1 if division by zero
-code 2 if completed
*/
char fullcalc(short *toc, long long *arg, short length, long long *result)
{

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
	char c;
	/*counter*/
	short i;
	/*
	-count of opening brackets
	-count of closing brackets
	-last position of opening bracket
	-last position of closing bracket
	*/
	short bo, bc, bop, bcp;
	while (((c = getchar()) != EOF) && (c != '\n'))
	{
		if(chksmb(*toc, *arg, bo, ) == 0)
			return 0;
	}
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
			sodes;
			break;
		case 1:
			sodez;
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
	long long arg[499];
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
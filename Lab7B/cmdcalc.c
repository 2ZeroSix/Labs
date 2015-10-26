#include <stdio.h>
#include "cmdcalc.h"

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
char readexep(char *ecxep)
{
	char stack[1000];

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
*/
void output(char checker, long long result)
{

}
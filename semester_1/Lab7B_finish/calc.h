#ifndef __CALC_H__
#define __CALC_H__
#define obra 500
#define cbra 501
#define exend 502
#define plus 503
#define minus 504
#define mult 505
#define split 506

static char *outcode[] = { "Syntax error", "Division by zero" };

/*
Calculating exception
INPUT
-pointer to start of exception in reverse polish notation <*excep>
OUTPUT
-if completed
--code <2>
-if division by zero
--code <1>
*/
char fullcalc(short *excep, long long args[]);
/*
Read with check and change infix notation to reverse polish
INPUT
- massive for exception <*exep>
OUTPUT
- if syntax error
-- code <0>
- if completed
-- code <1>
*/
char readexcep(short *excep, long long args[]);
/*
Print result of work
INPUT
- output code <checker>
- result of calculation	<result>
CHANGES
- if checker == 2
--print result of calculation
- else
--print code of error switch(checker)
*/
void output(char checker, long long result);
#endif // __CALC_H__
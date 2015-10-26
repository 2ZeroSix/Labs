#include "calc.h"
#include "cmdcalc.h"

void main()
{
	char checker;
	long long result;
	char excep[1000];
	if(checker = readexep(stack, excep))
	{
		checker = fullcalc(excep, &result);
	}
	output(checker, result);
}
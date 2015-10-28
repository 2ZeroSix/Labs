#include "calc.h"
#include "cmdcalc.h"

void main()
{
	char checker;
	long long args[500] = {0};
	short excep[1001];
	if(checker = readexep(excep, args))
	{
		checker = fullcalc(excep, args);
	}
	output(checker, result);
}
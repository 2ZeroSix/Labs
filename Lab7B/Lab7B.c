#include "calc.h"

void main()
{
	char checker;
	short excep[1001];
	long long args[500] = { 0 };

	if (checker = readexcep(excep, args))
	{
		checker = fullcalc(excep, args);
	}
	output(checker, args[0]);
}
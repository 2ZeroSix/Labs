#include "calc.h"

void main()
{
	char checker;
	short excep[1001];
	long long args[500] = { 0 };
	int i;
	if (checker = readexcep(excep, args))
	{
//		for (i = 0; excep[i] != exend; i++)
//			printf("%d\n", excep[i]);
		checker = fullcalc(excep, args);
	}
	output(checker, args[0]);
}
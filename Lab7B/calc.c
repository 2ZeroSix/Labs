#include "calc.h"
#include "funsym.h"


/*
Calculating exception
INPUT
-pointer to start of exception <*excep>
OUTPUT
-if completed
--code <2>
-if division by zero
--code <1>
*/
char fullcalc(short *excep, long long *args)
{
	short i, arg1 = 0, arg2 = 0;
	for(i = 0; excep[i] != exend; i++)
	{
		if (excep[i] < 500)
		{
			arg1 = arg2;
			arg2 = i;
		}
		if (excep[i] == )
	}
}
#include "unlimnums.h"

char isnumch(const char arg)
{
	if ((arg >= '0') && (arg <= '9'))
		return 1;
	return 0;
}

char* ba_add(char* arg1, char* arg2)
{
	char* res = NULL;
	printf("1 step\n");
	printf("%d, %d\n", arg1[0], arg2[0]);
	if (arg1 && arg2)
	{
		int l1, l2, lmax, lmin, i, n1, n2;
		printf("2 step\n");
		l1 = strlen(arg1);
		l2 = strlen(arg2);
		lmax = ((l1 > l2) ? l1 : l2) + (((l1 == l2) && ((arg1[0] - '0' + arg2[0] - '0') > 9)) ? 1 : 0);
		lmin = (l1 < l2) ? l1 : l2;
		printf("l1: %d l2: %d lmax: %d lmin: %d\n", l1, l2, lmax, lmin);
		res = (char*)malloc(sizeof(char)*(lmax));
		for (i = 0; i < lmax; i++)
			res[i] = 0;
			printf("3 step\n");
		for (i = 1; i <= lmin; i++)
		{
			res[lmax - i] += arg1[l1 - i] - '0' + arg2[l2 - i];
			if (res[lmax - i] > '9')
			{
				res[lmax - i] -= 10;
				res[lmax - i - 1] += 1;
			}
			printf("%c\n", res[lmax - i]);
		}
		printf("4 step\n");
		for(i = lmin + 1; i < lmax; i++)
		{
			res[lmax - i] += (l1 > l2) ? arg1[l1 - i] : arg2[l2 - i];
			if (res[lmax -	i] > '9')
			{
				res[lmax - i -	1] += 1;
				res[lmax - i] -= 10;
			}
			printf("%c\n", res[lmax - i]);
		}
		(lmax == (l2 + 1))
	}
	return res;
}




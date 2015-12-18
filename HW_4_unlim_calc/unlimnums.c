#include "unlimnums.h"

static char* errlnm[4] = {"nothing", "syntax error", "division by zero", "pointer to zero"};
static int errln = 0;
static char znfor[2];
static char forwardln = 0;

const char* errorln()
{
	return errstrln[errln];
}


const char* ba_sub(const char* arg1, const char* arg2)
{
	char* res = NULL;
	if(arg1 && arg2
	{
		static int l1 = strlen(arg1), l2 = strlen(arg2), lmax, lmin;
		if(!forwardln)
		{
			
		}
		
	}
	else
	{
		errnumln = 3;
	}
	return res;
}

const char* ba_add(const char* arg1, const char* arg2)
{
	char* res = NULL;
	if (arg1 && arg2)
	{
		static int l1, l2, lmax, lmin, i;
		char zn = '+';
		l1 = strlen(arg1);
		l2 = strlen(arg2);
		if (!forwardln)
		{
			if ((arg1[l1 - 1] == '-') && (arg2[l2 - 1] == '-'))
			{
				zn = '-';
			}
			else
			{
				// if (arg1[l1 - 1] == '-')
				// {
				// 	return ba_sub(arg2, arg1);
				// }
				// if (arg2[l2 - 1] == '-')
				// {
				// 	return ba_sub(arg1, arg2);
				// }
			}
		}
		if (l1 > l2)
		{
			lmax = l1 + 1;
			lmin = l2;
		}
		else
		{
			lmax = l2 + 1;
			lmin = l1;
		}
		// printf("l1 %d\nl2 %d\nlmax %d\nlmin %d\n", l1, l2, lmax, lmin);
		res = (char*)malloc(sizeof(char)*(lmax + 1));
		for (i = 0; i <= lmax; i++)
			res[i] = 0;
		for (i = 0; i < (lmin - 1); i++)
		{
			if(!(isdigit(arg1[i]) && isdigit(arg2[i])))
			{
				free(res);
				errnumln = 1;
				return NULL;
			}
			res[i] += arg1[i] - '0' + arg2[i];
			if (res[i] > '9')
			{
				res[i] -= 10;
				res[i + 1] += 1;
			}
		}
		for (; i < (lmax - 2); i++)
		{
			if(!(isdigit(arg1[i]) || isdigit(arg2[i])))
			{
				free(res);
				errnumln = 1;
				return NULL;
			}
			res[i] += (l1 > l2) ? arg1[i] : arg2[i];
			if (res[i] > '9')
			{
				res[i] -= 10;
				res[i + 1] += 1;
			}
		}
		if (res[i] != 0)
			res[i++] += '0';
		res[i] = zn;
	}
	else
	{
		errnumln = 3;
	}
	return res;
}




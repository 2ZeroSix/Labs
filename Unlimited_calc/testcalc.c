#include "unlimnums.h"
#include <stdio.h>

void main()
{
	// s1 = rlnum();
	// s2 = rlnum();
	const char* res = ba_add("0007+\0", "0003+\0");
	printf("%s\n", (res != NULL) ? res : errorln());
	free((char*)res);
	return;
}
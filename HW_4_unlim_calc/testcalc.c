#include "unlimnums.h"
#include <stdio.h>

void main()
{
	// s1 = rlnum();
	// s2 = rlnum();
	const char* res = ba_add("9999-", "3-\0");
	printf("%s\n", (res != NULL) ? res : ba_error_info());
	free((char*)res);
	return;
}

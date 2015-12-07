#ifndef _UNLIMNUMS_H_
#define _UNLIMNUMS_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


/*
output
-last error
*/
const char* errorln();



/*
read long number from stdin
output
	-string with long number
*/
const char* rlnum();


/*
input
	- 2 const strings in the form: ('0', '1', ..., '9')...('0', '1', ..., '9')('+', '-')
	e.g. 
	number 1000 -> "0001+"
	number -503 -> "305-"
output
	-if completed
		- const string with result of operation in the same form
	-else
		- NULL
*/
const char* ba_add(const char* arg1, const char* arg2);

const char* ba_sub(const char* arg1, const char* arg2);

const char* ba_mul(const char* arg1, const char* arg2);

const char* ba_div(const char* arg1, const char* arg2);

const char* ba_mod(const char* arg1, const char* arg2);

#endif
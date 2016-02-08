#ifndef _UNLIMNUMS_H_
#define _UNLIMNUMS_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


/*
ERROR info
output
	-string with info about last error
*/
char* ba_error_info();


/* CORRECT FORM
correct form: ('0', '1', ..., '9')...('0', '1', ..., '9')('+', '-')
e.g.
number "1000" -> "0001+"
number "-503" -> "305-"
*/

/* checker
input
	- const char* (not NULL)
output
	- if CORRECT FORM
		- 1
	- else
		- 0
*/
char ba_iscorrectform(const char* arg);
//same for normal form
char ba_isnormalform(const char* arg);

// translators without any checks
const char* ba_tonormalform(const char* arg);
const char* ba_tocorrectform(const char* arg);

/*
read long number from FILE(read word from stream, check it with ba_isnormalform, translate with ba_tocorrectform, return)
input
	- pointer to the stream
output
	- const string with long number in the correct form
*/
const char* ba_read(FILE* in);

/*
input
	- 2 const strings in the correct form
output
	- if completed
		- const string with result of operation in the correct form
	- else
		- NULL
*/
// sum
const char* ba_add(const char* arg1, const char* arg2);
// subtraction
const char* ba_sub(const char* arg1, const char* arg2);
// multiplication
const char* ba_mul(const char* arg1, const char* arg2);
// division
const char* ba_div(const char* arg1, const char* arg2);
// modulo
const char* ba_mod(const char* arg1, const char* arg2);

#endif

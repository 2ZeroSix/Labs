#ifndef _ENDE64_H_
#define _ENDE64_H_
#include <stdio.h>
#include <string.h>
#define encode "-e"
#define decode "-d"
#define ignore "-i"

/*
translate to b64
Input
-number of symb in b64 alphabet
Output
-if completed
--symb ib b64 alphabet
-if error
--'-'
*/
char b64sym(char sym);

/*translate to number of simb
Input
-symb in b64 alphabet
Output
-if completed
--number of symb in b64 alphabet
-if error
--'-'
*/
char b64num(char sym);

/*
Text to Base64
Input
-input file <*in>
-output file <*out>
Changes
-print Base64 code in <*out>
*/
void encoder(FILE *in, FILE *out);

/*
Base64 to text
Input
-input file  <*in>
-output file <*out>
-ignore mode <im>
Changes
-print text in <*out>
Output
-code <1> if completed
-code <0> if wrong value in file
*/
char decoder(FILE *in, FILE *out, int im);

/*
input
-count of arguments <argc>
-arguments <**argv>
-pointer for input file <*out>
-for output file <*out>
-checker <check>
changes
-*in = pointer to input file
-*out = pointer to output file
-check[i - 1] = <not zero code> if argument[i] 	correct
output
-code <0> if arguments incorrect
-code <any int > 0> if arguments correct
*/
char checkmode(int argc, char *argv[], FILE **in, FILE **out, int *check);

/*
Print outcode
Input
-checks <*check>
-count of arguments <argc>
-argumentts <**argv>
*/
void output(int *check, int argc, char *argv[]);

#endif _ENDE64_H_
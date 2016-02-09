#ifndef _CALC_H_
#define _CALC_H_


#include "stack.h"
#include <math.h>
#include <string.h>
#include <ctype.h>


//operators codes
//numeric operator
#define numeric 0
//open bracket
#define obr 1
//close bracket
#define cbr 2
//4 priority
//plus
#define pls 3
//minus
#define mns 4
//unary minus
#define mnsu 5
//3 priority
//multiplication
#define mlt 6
//division
#define dvs 7
//2 priority
//grade
#define grd 8
//1 priority
//logarithm 10
#define lgrt 9
//logarithm e
#define lgre 10
//tangent
#define tng 11
//cotangent
#define ctng 12
//sinus
#define sns 13
//cosine
#define csn 14
//error operator
#define errorop 15


/*
put exp element in expression (read from stdin if it need) or stack with check
Input
-last input symbol
-head of expression
-head of stack
Changes
-read new symbols from stdin and save unused symbol(last input symbol) in var c
-save last operator code in variable lastop
Output
-if complete
--NULL
-if FAILED
--pointer to structure _expr with code of bad operator of expression
*/
expr* putexp(char* c, expr** head, expr** stack);

/*
read expression in infix notation from stdin and transfer to postfix notation
input
-pointer to pointer to structure _expr
Output
-if complete
--<1>
-if FAILED
--<0>
*/
char readexp(expr** head);

/*
calculate expression in postfix notation
Input
-pointer to structure _expr
Output
-if complete
--pointer to result
-if division by zero
--NULL pointer
*/
typeexp* calcexp(expr** head);


#endif
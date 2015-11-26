#ifndef _CALC_H_
#define _CALC_H_
//operators codes
//numeric operator
#define numeric 0
//open bracket
#define obr 1
//close bracket
#define cbr 2
//plus
#define pls 3
//minus
#define mns 4
//multiplication
#define mlt 5
//division
#define dvs 6
//logarithm 10
#define lgrt 7
//logarithm e
#define lgre 8
//tangent
#define tng 9
//cotangent
#define ctng 10
//sinus
#define sns 11
//cosine
#define csn 12
//grade
#define grd 13
//error operator
#define errorop 14

#include "stack.h"

/*
put exp element in expression (read from stdin if it need) or stack with check
Input
-readed char
-head of expression
-head of stack
Output
-if complete
--NULL
-if FAILED
--poiter to struct _exp with code of bad operator of expression
*/
exp* putexp(char* c, exp** head, exp** stack)

/*
read expression in infix notation and transfer to postfix notation
input
-pointer to pointer to structure _exp
Output
-if complete
--<1>
-if FAILED
--<0>
*/
char readexp(exp** head);

/*
calculate expression in postfix notation
Input
-pointer to structure _exp
Output
-if complete
--pointer to result
-if division by zero
--NULL pointer
*/
typeexp* calcexp(exp* head)


#endif
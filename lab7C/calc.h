#ifndef _CALC_H_
#define _CALC_H_


#include "stack.h"
#include "math.h"


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
//3 priority
//multiplication
#define mlt 5
//division
#define dvs 6
//2 priority
//grade
#define grd 7
//1 priority
//logarithm 10
#define lgrt 8
//logarithm e
#define lgre 9
//tangent
#define tng 10
//cotangent
#define ctng 11
//sinus
#define sns 12
//cosine
#define csn 13
//error operator
#define errorop 14


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
expr* putexp(char* c, expr** head, expr** stack);

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
char readexp(expr** head);

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
typeexp* calcexp(expr* head);


#endif
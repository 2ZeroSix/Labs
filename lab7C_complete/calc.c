#include "calc.h"

// last input operator code
static char lastop = errorop;



expr* putexp(char* c, expr** head, expr** stack)
{
	if ((*c >= '0') && (*c <= '9'))
	{
		expr* temp = (expr*)malloc(sizeof(expr));
		temp->op = numeric;
		if ((lastop == cbr) || (lastop == numeric))
			return temp;
		typeexp num = 0;
		do
		{
			num = num * 10 + (*c) - '0';
		} while (((*c = getchar()) >= '0') && (*c <= '9')); 
		if ((*c == '.') || (*c == ','))
		{
			typeexp ten = 10;
			if(typeexpnum)	// if dot illegal
				return temp; 
			*c = getchar();
			do
			{
				num += ((*c) - '0') / ten;
				ten *= 10;
			} while (((*c = getchar()) >= '0') && (*c <= '9'));
		}
		lastop = numeric;
		temp->num = num;
		pushexp(head, temp);
	}
	else
	{
		char tc;
		expr* temp = (expr*)malloc(sizeof(expr));
		*c = tolower(*c);
		switch(*c)
		{
			case '(':
				temp->op = obr;
				if((lastop == cbr) || (lastop == numeric))
					return temp;
				break;
			case ')':
				temp->op = cbr;
				if((lastop == errorop) || (lastop == obr) || (lastop >= pls))
					{
						return temp;
					}
				while((*stack)->op != obr)
				{
					pushexp(head, popexp(stack));
					if (*stack == NULL)
					{
						return temp;
					}
				}
				free(popexp(stack));
				break;
			case '+':
				temp->op = pls;
				if((lastop == errorop) || (lastop == obr) || (lastop >= pls))
					return temp;
				while((*stack != NULL) && (((*stack)->op) >= pls))
					pushexp(head, popexp(stack));
				break;
			case '-':
				if((lastop == errorop) || (lastop == obr))
				{
					temp->op = mnsu;
 				}
 				else
 				{
					temp->op = mns;
 				}
				if((lastop >= pls) && (lastop != errorop))
					return temp;
				while((*stack != NULL) && (((*stack)->op) >= pls))
					pushexp(head, popexp(stack));
				break;
			case '*':
				temp->op = mlt;
				if((lastop == errorop) || (lastop == obr) || (lastop >= pls))
					return temp;
				while((*stack != NULL) && ((*stack)->op >= mlt))
					pushexp(head, popexp(stack));
				break;
			case '/':
				temp->op = dvs;
				if((lastop == errorop) || (lastop == obr) || (lastop >= mlt))
					return temp;
				while((*stack != NULL) && ((*stack)->op >= mlt))
					pushexp(head, popexp(stack));
				break;
			case 'l':
				temp->op = errorop;
				if(((tc = getchar()) == 'g') || ((tc == 'o') && ((tc = getchar()) == 'g')))
				{
					temp->op = lgrt;
				}
				else if((tc == 'n'))
				{
					temp->op = lgre;
				}
				else
				{
					return temp;
				}
				if((lastop == cbr) || (lastop == numeric))
					return temp;
				break;
			case 's':
				temp->op = sns;
				if(!((getchar() == 'i') && (getchar() == 'n')))
					return temp;
				if((lastop == cbr) || (lastop == numeric))
					return temp;
				break;
			case 'c':
				temp->op = csn;
				if(!((getchar() == 'o') && (getchar() == 's')))
					return temp;
				if((lastop == cbr) || (lastop == numeric))
					return temp;
				break;
			case 't':
				temp->op = tng;
				if((!((tc  = getchar()) == 'g')) && (!((tc == 'a') && ((tc = getchar()) == 'n'))))
					return temp;
				if((lastop == cbr) || (lastop == numeric))
					return temp;
				break;
			case '^':
				temp->op = grd;
				if((lastop == errorop) || (lastop == obr) || (lastop >= pls))
					return temp;
				while((*stack != NULL) && ((*stack)->op > grd))
					pushexp(head, popexp(stack));
				break;
			case 'e':
				temp->op = numeric;
				temp->num = 2.7182818284590452353602874713527;
				if ((lastop == cbr) || (lastop == numeric))
					return temp;
				break;
			case 'p':
				temp->op = numeric;
				temp->num = 3.1415926535897932384626433832795;
				if ((getchar() != 'i') || (lastop == cbr) || (lastop == numeric))
					return temp;
				break;
			default:
				temp->op = errorop;
				return temp;
				break;
		}
		lastop = temp->op;
		if ((lastop != cbr) && (lastop != numeric))
			pushexp(stack, temp);
		if (lastop == numeric)
			pushexp(head, temp);
		*c = getchar();
	}
	return NULL;
}

char readexp(expr** head)
{
	expr *stack = NULL, *temp = NULL;
	char c = getchar();
	*head = NULL; 
	while (((c != EOF) && (c != '\n')))
	{
		if(temp = putexp(&c, head, &stack))
			{
				free(temp);
				return 0;
			}
	}
	if (lastop >= pls)
		return 0;
	while(stack != NULL)
	{
		if (stack->op == obr)
		{
			freeexp(&stack);
			return 0;
		}
		pushexp(head, popexp(&stack));
	}
	revertexp(head);
	lastop = errorop;
	return 1;
}

typeexp* calcexp(expr** head)
{
	expr *stack = NULL, **temp = (expr**)malloc(sizeof(expr*)*2), *cur;
	while(*head)
	{
		cur = popexp(head); // добавить освобождение структур со знаками операции
		switch (cur->op)
		{
			case numeric:
				pushexp(&stack,  cur);
				break;
			case pls:
				temp[0] = popexp(&stack);
				temp[1] = popexp(&stack);
				temp[0]->num += temp[1]->num;
				free(temp[1]);
				pushexp(&stack, temp[0]);
				break;
			case mns:
				temp[0] = popexp(&stack);
				temp[1] = popexp(&stack);
				temp[0]->num = temp[1]->num - temp[0]->num;
				free(temp[1]);
				pushexp(&stack, temp[0]);
				break;
			case mnsu:
				temp[0] = popexp(&stack);
				temp[0]->num = -temp[0]->num;
				pushexp(&stack, temp[0]);
				break;
			case mlt:
				temp[0] = popexp(&stack);
				temp[1] = popexp(&stack);
				temp[0]->num *= temp[1]->num;
				free(temp[1]);
				pushexp(&stack, temp[0]);
				break;
			case dvs:
				temp[0] = popexp(&stack);
				temp[1] = popexp(&stack);
				if(temp[0]->num == 0)
				{
					free(temp[1]);
					freeexp(&stack);
					return NULL;
				}
				temp[0]->num = temp[1]->num / temp[0]->num;
				free(temp[1]);
				pushexp(&stack, temp[0]);
				break;
			case lgrt:
				temp[0] = popexp(&stack);
				if(temp[0]->num <= 0)
				{
					freeexp(&stack);
					return NULL;
				}
				temp[0]->num = log10(temp[0]->num);
				pushexp(&stack, temp[0]);
				break;
			case lgre:
				temp[0] = popexp(&stack);
				if(temp[0]->num <= 0)
				{
					freeexp(&stack);
					return NULL;
				}
				temp[0]->num = log(temp[0]->num);
				pushexp(&stack, temp[0]);
				break;
			case sns:
				temp[0] = popexp(&stack);
				temp[0]->num = sin(temp[0]->num);
				pushexp(&stack, temp[0]);
				break;
			case csn:
				temp[0] = popexp(&stack);
				temp[0]->num = cos(temp[0]->num);
				pushexp(&stack, temp[0]);
				break;
			case tng:
				temp[0] = popexp(&stack);
				temp[0]->num = tan(temp[0]->num);
				pushexp(&stack, temp[0]);
				break;
			case grd:
				temp[0] = popexp(&stack);
				temp[1] = popexp(&stack);
				temp[0]->num = pow(temp[1]->num, temp[0]->num);
				free(temp[1]);
				pushexp(&stack, temp[0]);
				break;
			default:
			printf("opcode: %d\nnum%d\n",cur->op, cur->num);
			printf("i don't know what happen\n");
			break;
		}
		if (cur->op != numeric)
			free(cur);

	}
	return &(stack->num);
}
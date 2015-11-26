#include "calc.h"

exp* putexp(char* c, exp** head, exp** stack)
{
	static char lastop = errorop;
	if ((*c >= '0') && (*c <= 9))
	{
		exp* temp = (exp*)malloc(sizeof(exp));
		typetemp num = 0;
		do
		{
			num = num * 10 + (*c) - '0';
		} while (((c = getchar()) >= 0) && (c <= 9)); 
		if ((c == '.') || (c == ','))
		{
			*c = getchar();
			do
			{
				int ten = 10;
				num += ((*c) - '0') / ten;
				ten *= 10;
			} while (((*c = getchar()) >= 0) && (*c <= 9));
		}
		lastop = temp->op = numeric;
		temp->num = num;
		pushexp(head, temp);
	}
	else
	{
		exp* temp = (exp*)malloc(sizeof(exp));
		switch(*c)
		{
			case '(':
				temp->op = obr;
				if((lastop == cbr) || (lastop == numeric)))
					return temp;
				break;
			case ')':
				if((lastop == errorop) || (lastop == obr) || (lastop >= pls))
					{
						temp->op = errorop
						return temp;
					}
				while((*stack)->op != obr)
				{
					pushexp(head, popexp(stack));
					if (*stack == NULL)
					{
						return 0;
					}
				}
				free(popexp(stack));
				break;
			case '+':
				temp->op = pls;
				if((lastop == errorop) || (lastop == obr) || (lastop >= pls))
					return temp;
				while((*stack != NULL) && ((*stack)->op => pls))
					pushexp(head, popexp(stack));
				break;
			case '-':
				temp->op = mns;
				if((lastop == errorop) || (lastop == obr) || (lastop >= pls))
					return temp;
				while((*stack != NULL) && ((*stack)->op => pls))
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
				if(((tc = getchar()) == 'o') && ((tc = getchar()) == 'g'))
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
				while((*stack != NULL) && ((*stack)->op > csn))
					pushexp(head, popexp(stack));
				break;
			case 's':
				if((getchar() == 'i') && (getchar() == 'n'))
				{
						temp->op = sns;
				}
				else
				{
					return temp;
				}
				if((lastop == cbr) || (lastop == numeric))
					return temp;
				while((*stack != NULL) && ((*stack)->op > csn))
					pushexp(head, popexp(stack));
				break;
			case 'c':
				if((getchar() == 'o') && (getchar() == 's'))
				{
					temp->op = cns;
				}
				else
				{
					return temp;
				}
				if((lastop == cbr) || (lastop == numeric))
					return temp;
				while((*stack != NULL) && ((*stack)->op > csn))
					pushexp(head, popexp(stack));
				break;
			case '^':
				temp->op = grd;
				if((lastop == errorop) || (lastop == obr) || (lastop >= plus))
					return temp;
				break;
			default:
				temp->op = errorop;
				return temp;
				break;
		}
		lastop = temp->op;
		pushexp(stack, temp);
		*c = getchar();
	}
	return NULL;
}

char readexp(exp** head)
{
	exp *stack = NULL, *temp = NULL;
	char c = getchar();
	*head = NULL;
	while (((c != EOF) && (c != '\n'))
	{
		if((temp = putexp(c, head, &stack, lastop)) != NULL)
			{
				free(temp);
				return 0;
			}
	}
	while(stack != NULL)
	{
		if (stack->op == obr)
			return 0;
		pushexp(head, popexp(stack));
	}
	return 1;
}

char calcexp(exp* head)
{

}
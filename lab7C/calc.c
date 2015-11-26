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
				temp->errorop;
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
				if((lastop == errorop) || (lastop == obr) || (lastop >= plus))
					return temp;
				while((*stack != NULL) && ((*stack)->op > grd))
					pushexp(head, popexp(stack));
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
		pushexp(head, popexp(&stack));
	}
	revertexp(head);
	return 1;
}

char calcexp(exp* head)
{
	exp *stack = NULL, *temp[2], *cur;
	while(head)
	{
		cur = popexp(&head);
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
				temp[0]->num = log10(temp[0]->num)
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
			case tng;
				temp[0] = popexp(&stack);
				temp[0]->num = tan(temp[0]->num);
				pushexp(&stack, temp[0]);
				break;
			case grd;
				temp[0] = popexp(&stack);
				temp[1] = popexp(&stack);
				temp[0]->num = pow(temp[1]->num, temp[0]->num);
				free(temp[1]);
				pushexp(&stack, temp);
				break;
			default:
			printf("i don't know what happen\n");
		}

	}
	return &(stack->num)
}
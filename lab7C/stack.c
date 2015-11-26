#include "stack.h"


exp* popexp(exp** head)
{
	exp* temp = NULL;
	if (head)
	{
		temp = *head;
		if (*head)
			*head = (*head)->next;
	}
	return temp;
}

void pushexp(exp** head, exp* push)
{
	if (push && head)
	{
		push->next = *head;
		(*head) = push 
	}
	return;
}

void freeexp(exp** head)
{
	exp* temp;
	while(head)
	{
		temp = (*head);
		(*head) = (head->next)
		free(temp);
	}
}

void revertexp(exp** head)
{
	exp *cur = NULL, *prev1 = NULL, *prev2 = NULL;
	if(*head)
		cur = *head;
	while(cur)
	{ 
		if(prev1)
		{
			prev1->next = prev2; 
		}
		prev2 = prev1;
		prev1 = cur;
		cur = cur->next;
	}
	if (prev1)
		prev1->next = prev2;
	*head = prev1;
	return;
}
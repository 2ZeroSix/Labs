#include "stack.h"

exp* popexp(exp** head)
{
	exp* temp = NULL;
	if (head != NULL)
	{
		temp = *head;
		if (*head != NULL)
			*head = (*head)->next;
	}
	return temp;
}

void pushexp(exp** head, exp* push)
{
	if (push != NULL)
	{
		push->next = *head;
		(*head) = push 
	}
	return;
}

void freeexp(exp** head)
{
	exp* temp;
	while(head != NULL)
	{
		temp = (*head);
		(*head) = (head->next)
		free(temp);
	}
}
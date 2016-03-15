#include <stdio.h>
#include <stdlib.h>

typedef struct _stack {
  int value;
  struct _stack* next;
}stack;

stack* push(stack* stk, int value) {
	stack* new = (stack*)calloc(1, sizeof(stack));
	new->value = value;
	new->next = stk;
	return new;
}

int pop(stack** stk) {
	if(stk && *stk) {
		stack* tmp = *stk;
		int value = tmp->value;
		*stk = (*stk)->next;
		free(tmp);
		return value;
	}
	return 0;
}

void free_stk(stack** stk) {
	while(stk && (*stk))
	{
		stack* tmp = (*stk);
		(*stk) = (*stk)->next;
		free(tmp);
	}
}

int main(int argc, char const *argv[])
{
	int c;
	stack* stk = NULL;
	while(((c = getchar()) != EOF) && (c != '\n')) {
		switch(c) {
			case '(':
				stk = push(stk, c);
				break;
			case '[':
				stk = push(stk, c);
				break;
			case '{':
				stk = push(stk, c);
				break;
			case ')':
				if(pop(&stk) != '('){
					printf("NO");
					free_stk(&stk);
					return 0;
				}
				break;
			case ']':
				if(pop(&stk) != '['){
					printf("NO");
					free_stk(&stk);
					return 0;
				}
				break;
			case '}':
				if(pop(&stk) != '{'){
					printf("NO");
					free_stk(&stk);
					return 0;
				}
				break;
			default:
				break;
		}
	}
	if(stk) {
		printf("NO");
	}
	else {
		printf("YES");
	}
	free_stk(&stk);
	return 0;
}
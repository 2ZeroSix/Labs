#define _CRT_SECURE_NO_WARNINGS
#define maxline 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sorts for qsort
int sortinti(const int* num1, const int* num2)
{
	return *num1 - *num2;
}

int sortstri(const char** str1, const char** str2)
{
	return strcmp(*str1, *str2);
}

int sortintd(const int* num1, const int* num2)
{
	return *num2 - *num1;
}

int sortstrd(const char** str1, const char** str2)
{
	return strcmp(*str2, *str1);
}

/*
printout array
Input
-array
-type of array('i' for integer, other for string
-count of elements
*/
void printout(void* arr, char type, int count)
{
	int i;
	printf("Printout:\n");
	if (type == 'i')
	{
		for (i = 0; i < count; i++)
		{
			printf("%d: %d\n", i, ((int*)arr)[i]);
		}
	}
	else
	{
		for(i = 0; i < count; i++)
		{
			printf("%d: %s\n", i, ((char**)arr)[i]);
		}
	}
	return;
}

/*
sort array
Input
-array
-type of array
-count of elements
*/
void sort(void* arr, char* type, int count)
{
	printf("Sort:\ntype of arr: %s\nType of sort: %s\nCount of elements: %d\n", (type[0] == 'i') ? "integer" : "string", (type[1] == 'i') ? "increase" : "decrease", count, (type[0] == 'i') ? "integer" : "strings");
	if(type[0] == 'i')
	{
		qsort(arr, count, sizeof(int), (int(*) (const void*, const void*)) ((type[1] == 'i') ? sortinti : sortintd));
	}
	else
	{
		qsort(arr, count, sizeof(char*), (int(*) (const void*, const void*)) ((type[1] == 'i') ? sortstri : sortstrd));
	}
	return;
}

/*
Read input information
Input
-pointer to variable for count of elements
-pointer to first element of array for type of array and type of sort
Output
-pointer to the first element of array (void*)
*/
void* readin(int* count, char* type)
{
	//counter
	int i;
	//temp
	char c;
	printf("readin\n");
	printf("print count of elements: ");
	while(((c = getchar()) != '\n') && (c != EOF))
		*count = (*count) * 10 + c - '0';
	printf("\nIncrease or decrease? ('i'... for increase, other for decrease: ");
	type[1] = getchar();
	while(((c = getchar()) != '\n') && (c != EOF));
	printf("\nWhich type of array ('i'... for integer, other for string)): ");
	if((type[0] = getchar()) == 'i')
	{
		int* arr = (int*)malloc((*count)*sizeof(int));
		while((c = getchar()) != '\n');
		printf("\nprint elements\n");
		for (i = 0; i < *count; i++)
		{
			while(((c = getchar()) < '0') || (c > '9'));
			arr[i] = 0;
			while((c >= '0') && (c <= '9'))
			{
				arr[i] = arr[i]*10 + c -'0';
				c = getchar();
			}
		}
		return (void*)arr;
	}
	else
	{
		//counter
		int j;
		char** arr = (char**)malloc(sizeof(char*)*(*count));
		printf("\nprint elements\n");
		while((c = getchar()) != '\n');
		for (i = 0; i < *count; i++)
		{
			arr[i] = (char*)malloc(sizeof(char*)*(*count));
			j = 0;
			while ((j < 99) && ((c = getchar()) != '\n') && (c != EOF))
			{
				arr[i][j++] = c; 
			}
			arr[i][j] = '\0';
		}
		return (void*)arr;
	}
}

void main()
{
	//count of elements
	int count = 0;
	//type of array and type of sort
	char type[2];
	//array
	void* arr = readin(&count, type);
	sort(arr, type, count);
	printout(arr, type[0], count);
	if (type[0] != 'i')
	{
		int i;
		for (i = 0; i < count; i++)
			free(((char**)arr)[i]);
	}
	free(arr);
	printf("Press enter\n");
	getchar();
	return;
}
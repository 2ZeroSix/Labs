#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student
{
	char name[20];
	float avrate;
	int age;
	struct _student *next;
}student;

int sortname(const void* std1, const void* std2)
{
	return strcmp(((student*)(std1))->name, ((student*)(std2))->name);
}

int sortavrate(const void* std1, const void* std2)
{
	if(((student*)(std1))->avrate == ((student*)(std2))->avrate)
		return 0;
	if(((student*)(std1))->avrate > ((student*)(std2))->avrate)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int sortage(const void* std1, const void* std2)
{
	return (((student*)(std1))->age - ((student*)(std2))->age);
}

void printfsort(student* studmas, int count)
{
	int i;
	printf("sort\n");
	for (i = 0; i < count; i++)
	{
		printf("%s %f %d\n", studmas[i].name, studmas[i].avrate, studmas[i].age);
	}
}

void main()
{
	student arr[5];
	int i;
	char c;
	for(i = 0; i < 5; i++)
	{
	int j = 0;
	while((c = getchar()) != ' ') 	
	{
		arr[i].name[j++] = c;
	}
		arr[i].name[j] = '\0';
	scanf("%f %d", &(arr[i].avrate), &(arr[i].age));
	printf("%s %f %d\n", arr[i].name, arr[i].avrate, arr[i].age);
	getchar();
	}
	qsort(arr, 5, sizeof(student), sortname);
	printfsort(arr, 5);
	qsort(arr, 5, sizeof(student), sortavrate);
	printfsort(arr, 5);
	qsort(arr, 5, sizeof(student), sortage);
	printfsort(arr, 5);
	getchar();
}
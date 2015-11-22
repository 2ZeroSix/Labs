#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mnl 20

typedef struct _student
{
	char name[mnl];
	float avrate;
	int age;
	struct _student *next;
}student;

void pushlist(student *new, student **Head)
{
	new->next = *Head;
	*Head = new;
	return;
}

student poplist(student **Head)
{
	student *temp = *Head;
	*Head = (*Head)->next;
	return *temp;
}

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

void printfsort(student* studmas, FILE *out, int count)
{
	int i;
	for (i = 0; i < count; i++)
	{
		fprintf(out, "%s %f %d\n", studmas[i].name, studmas[i].avrate, studmas[i].age);
	}
}

void sortandprint(FILE *out1, FILE *out2, FILE *out3, student* studmas, int count)
{
	qsort(studmas, count, sizeof(student*), sortname);
	printfsort(studmas, out1, count);
	qsort(studmas, count, sizeof(student*), sortavrate);
	printfsort(studmas, out2, count);
	qsort(studmas, count, sizeof(student*), sortage);
	printfsort(studmas, out3, count);
	return;
}

char rstudlist(FILE *in, FILE *out1, FILE *out2, FILE *out3, student *studmas)
{
	int i, count = 0;
	char c;
	student *Head = NULL;
	while((c = getc(in)) != EOF)
	{
		i = 0;
		student *temp;
		do
		{
			temp->name[i++] = c;
		} while (((c =getc(in)) != ' ') && (i < mnl));
		if (c != ' ')
			return 0;
		fscanf(in, "%f %d", temp->avrate, temp->age);
		pushlist(temp, &Head);
		getc(in);
		count++;
	}
	studmas = (student**) malloc (sizeof(student*)*count);
	for (i = 0; i < count; i++)
	{
		studmas[i] = poplist(&Head);
	}
	return count;
}

int open(FILE **in, FILE **out1, FILE **out2, FILE **out3)
{
	if((*in = fopen("in.txt", "r")) == NULL)
 		return 0;
	if((*out1 = fopen("out1.txt", "w")) == NULL)
		return 0;
	if((*out2 = fopen("out2.txt", "w")) == NULL)
		return 0;
	if((*out3 = fopen("out3.txt", "w")) == NULL)
		return 0;
	return 1;
}

void main()
{
	FILE *in, *out1, *out2, *out3;
	student *studmas;
	int count;
	if(open(&in, &out1, &out2, &out3))
	{
		count = rstudlist(in, out1, out2, out3, &studmas);
		sortandprint(out1, out2, out3, studmas, count);
		free(studmas);
	}
	else
	{
		printf("wrong files");
	}
}
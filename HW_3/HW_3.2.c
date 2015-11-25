#define _CRT_SECURE_NO_WARNINGS

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

student* poplist(student **Head)
{
	student *temp = *Head;
	if (*Head != NULL)
	*Head = (*Head)->next;
	return temp;
}

int sortname(const student* std1, const student* std2)
{
	return strcmp(std1->name, std2->name);
}

int sortavrate(const student* std1, const student* std2)
{
	if (std1->avrate == std2->avrate)
		return 0;
	if (std1->avrate > std2->avrate)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int sortage(const student* std1, const student* std2)
{
	return (std1->age - std2->age);
}

void printfsort(student* studmas, FILE *out, int count)
{
	int i;
	printf("output\n");
	for (i = 0; i < count; i++)
	{
		fprintf(out, "%s %.2f %d\n", studmas[i].name, studmas[i].avrate, studmas[i].age);
	}
}

void sortandprint(FILE *out1, FILE *out2, FILE *out3, student* studmas, int count)
{
	printf("sort and print in files\n");
	qsort(studmas, count, sizeof(student), (int(*) (const void *, const void *)) sortname);
	printf("\tfirst sort -> ");
	printfsort(studmas, out1, count);
	qsort(studmas, count, sizeof(student), (int(*) (const void *, const void *)) sortavrate);
	printf("\tsecond sort -> ");
	printfsort(studmas, out2, count);
	qsort(studmas, count, sizeof(student), (int(*) (const void *, const void *)) sortage);
	printf("\tthird sort -> ");
	printfsort(studmas, out3, count);
	printf("Complete sort\n");
	return;
}

char rstudlist(FILE *in, FILE *out1, FILE *out2, FILE *out3, student **studmas)
{
	int i, count = 0;
	char c;
	student *temp, *stm, *Head = NULL;
	printf("reading input file:\n");
	while((c = getc(in)) != EOF)
	{
		student *newst = (student*)malloc(sizeof(student));
		i = 0;
		do
		{
			newst->name[i++] = c;
		} while (((c =getc(in)) != ' ') && (i < mnl - 1));
		if (c != ' ')
			return 0;
		while(i<mnl)
			newst->name[i++] = '\0';
		fscanf(in, "%f %d", &(newst->avrate), &(newst->age));
		pushlist(newst, &Head);
		getc(in);
		printf("\t%d: %s %.2f %d\n", count, newst->name, newst->avrate, newst->age);
		count++;
	}
	stm = *studmas = (student*) malloc ((sizeof(student)+sizeof(char)*20)*count);
	i = 1;
	while ((temp = poplist(&Head))!= NULL)
	{
		strcpy(stm[count - i].name, temp->name);
		stm[count - i].age = temp->age;
		stm[count - i].avrate = temp->avrate;
		i++;
		free(temp);
	}
	printf("\tCount: %d\nComplete read\n", count);
	return count;
}

int open(FILE **in, FILE **out1, FILE **out2, FILE **out3)
{
	printf("Open files\n");
	if((*in = fopen("in.txt", "r")) == NULL)
 		return 0;
 	printf("\tin\n");
	if((*out1 = fopen("out1.txt", "w")) == NULL)
		return 1;
	printf("\tout1\n");
	if((*out2 = fopen("out2.txt", "w")) == NULL)
		return 2;
	printf("\tout2\n");
	if((*out3 = fopen("out3.txt", "w")) == NULL)
		return 3;
	printf("\tout3\n");
	printf("complete open\n");
	return 4;
}

void main()
{
	FILE *in, *out1, *out2, *out3;
	student *studmas;
	int count, check;
	printf("Protocol:\n");
	if((check = open(&in, &out1, &out2, &out3)) == 4)
	{
		count = rstudlist(in, out1, out2, out3, &studmas);
		sortandprint(out1, out2, out3, studmas, count);
		free(studmas);
		printf("Complete all\n");
	}
	else
	{
		printf("ERROR:");
	}
	if (check > 0)
		fclose(in);
	if (check > 1)
		fclose(out1);
	if (check > 2)
		fclose(out2);
	if (check > 3)
		fclose(out3);
	getc(stdin);
}
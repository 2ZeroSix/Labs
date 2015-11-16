#include <stdio.h>
#define mnl 20

typedef struct _student
{
	char name[mnl];
	float avrate;
	int age;
	student *next;
} student;

void pushlist(student *new, student *Head)
{
	new->next = Head;
	return;
}

student* poplist(student **Head)
{
	student *temp = *Head;
	*Head = *(Head)->next;
	return *Head;
}

int sortname(student *std1, student *std2)
{
	return strcmp(std1->name, std2->name);
}

int sortavrate(student *std1, student *std2)
{
	if(std1->avrate == std2->avrate)
		return 0;
	if(std1->avrate > std2->avrate)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int sortage(student *std1, student *std2)
{
	return (std1->age - std2->age);
}

char sortandprint(FILE *in, FILE *out1, FILE *out2, FILE *out3);
{
	qsort
}

char rstudlist(FILE *in, FILE *out1, FILE *out2, FILE *out3, student ***studmas)
{
	int i, count = 0;
	student *Head = NULL;
	while((c = getc(in)) != EOF)
	{
		i = 0;
		student *temp;
		do
		{
			temp->name[i++] = c;
		} while (((c =getc(in)) != ' ') && (i < mnl);
		if (c != ' ')
			return 0;
		scanf_s("%f", temp->avrate, sizeof(float));
		scanf_s("%d", temp->age, sizeof(int));
		pushlist(temp, Head);
		getc(in);
		count++;
	}
	*studmas = (student**) malloc (sizeof(student*)*count);
	for (i = 0; i < count; i++)
	{
		*studmas[i] = poplist(&Head);
	}
	return count;
}

int openoutput(FILE **in, FILE **out1, FILE **out2, FILE **out3)
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
	FILE* in, out1, out2, out3;
	student **studmas;
	int count;
	if(open(&in, &out1, &out2, &out3))
	{
		count = rstudlist(in, out1, out2, out3, &studmas);
		sortandprint(in, out1, out2, out3, studmas, count);
		free(studmass);
	}
	else
	{
		printf("wrong files");
	}
}
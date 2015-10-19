#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "ctype.h"
int  chartoint(char simbol, int *dot, int i)
/*������� � ������������� ������������� �� �����������
�������� ������ �����, ��������� �� ������� ����� � ����� ��������� �������
1��� ���������� �������� �����,
2��� ���������� ������� ����� � 'dot' � ���������� ��� ���������� �����
3��� ���������� ��� ������*/
{
	if (simbol >= '0' && simbol <= '9')
	{
		return simbol - '0';
	}
	simbol = toupper(simbol);
	if (simbol >= 'A' && simbol <= 'F')
	{
		return simbol - 'A' + 10;
	}
	if (simbol == '.' && *dot == -1) /*������ ������� ����� � "dot"*/
	{
		*dot = i;
		return -1;
	}
	return -2; /*����� ������*/
}
char inttochar(int number)
/*������� � ���������� ������������� �� ��������������
�������� �������� �����
���������� ������ �����*/
{
	if (number >= 0 && number <= 9)
	{
		return number + '0';
	}
	if (number >= 10 && number <= 15)
	{
		return number + 'A' - 10;
	}
}
int  readfloat(int *number, int b1, int b2, int *end)
/*���������� ������� ������ ���������� �� ����, ���������� ����� "dot" � ����� "end"
�������� ������ �� ���������� ����, ��������� ������ ��������� � ���������  �� ���������� ��� ����������� ����� �����
1���������� ����� ��� 2��� ������*/
{
	int dot = -1; /*-1 �� ������ ���������� �����*/
	getchar();
	char simbol = getchar();
	int i;
	for (i = 0; (simbol != 'EOF') && (simbol != '\n'); i++)
	{
		if ((number[i] = chartoint(simbol, &dot, i)) == -2 || number[i] >= b1) /*���������� � ��������� ������*/
		{
			return 0;
		}
		simbol = getchar();
	}
	*end = i;/*������� �����*/
	if (dot == -1) dot = i;
	return dot;
}
void printfloat(int *number, int lenght1, int lenght2)
/*������
�������� ������ �� ���������� ����, ������� ����� ����� � ������� ������.
�������� ����� �����������.*/
{
	int i;
	for (i = lenght1 - 1; i >= 0; i--)
	{
		printf("%c", inttochar(number[i]));
	}
	if (lenght1 != lenght2)
	{
		printf(".");
		for (i = lenght1; i < lenght2; i++)
		{
			printf("%c", inttochar(number[i]));
		}
	}
	return;
}
void b1tob2(int *number1, int b1, int b2, int dot, int end, int *lenght1, int *lenght2, int *number2)
/*������� �� ������ ������� ��������� �� ������.
�������� ������ �� ���������� ����, ��������� ������ ���������, ������� ����� � ����� �����.
���������� ���������� ������ �� ���������� ���� � ������������� �������������, ������� ����� ����� � ������� ������*/
{
	int i;
	long long int Numb = number1[0];
	double Numbf, schet;
	/*����� �����*/
	for (i = 1; i < dot; i++) /*������ � ����������� �����*/
	{
		Numb = Numb*b1 + number1[i];
	}
	if (Numb == 0) /*�������� �������� ����� �����*/
	{
		number2[0] = 0;
		*lenght1 = 1;
	}
	else
	{
		for (i = 0; Numb != 0; i++)/*������� �� ������ ������� ���������*/
		{
			number2[i] = Numb%b2;
			Numb = Numb / b2;
		}
		*lenght1 = i;
	}
	/*������� �����*/
	if (dot != end) /*�������� ������� ������� �����*/
	{
		Numbf = 0;
		for (i = end - 1; i > dot; i--) /*������ � ����������� �����*/
		{
			Numbf = (number1[i] + Numbf) / b1;
		}
		for (i = *lenght1; Numbf != 0 && i<*lenght1 + 12; i++) /*������� �� ������ ������� ���������*/
		{
			schet = Numbf*b2;
			number2[i] = schet;
			Numbf = schet - number2[i];
		}
	}
	*lenght2 = i;
	return;
}
void main()
{
	int b1, b2, dot, end, number1[13], number2[46], lenght1, lenght2;
	/*��������� ������ ���������, ������� �����, ������� �����, ������ ��� �������������� ����, ������ ��� ����������� ����, ������� ����� ����� �����, ������� ����� ������� �����*/
	scanf("%d %d", &b1, &b2);
	if (b1 > 1 && b2 > 1 && b1 < 17 && b2 < 17) /*��������*/
	{
		dot = readfloat(number1, b1, b2, &end);/*������ ��������� �����*/
		if (dot && dot != (end - 1))/*��������*/
		{
			b1tob2(number1, b1, b2, dot, end, &lenght1, &lenght2, number2);/*�������*/
			printfloat(number2, lenght1, lenght2);/*������*/
			return;
		}
	}
	printf("bad input");
	return;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define codearg "�������⨬�� ���-�� ��㬥�⮢: %d\n��������� ���� 2, ���� 3\n\n"
#define codeopen "����୮ 㪠��� ���� �� 䠩�� : \"%s\"\n\n"
#define codeprice "�������⨬�� ���祭�� 業� : \"%s\"\n\n"
#define codemode "�������⨬�� ���祭�� ०��� : \"%s\"\n\n"
#define priceof "���� �� %s"
#define oftext "⥪��: "
#define ofsimbol "ᨬ���: "
#define ofword "᫮��: "
#define ofpage "��࠭���: "
#define countof "������⢮ "
#define simbols "ᨬ�����: "
#define words "᫮�: "
#define pages "��࠭��: "
#define codefull "����䥩� ��������� ��ப�: <��� 䠩��> <業� � �㡫��> <०��>\n\n-��� 䠩�� - ���� � ⥪�⮢��� 䠩��\n\n-���� � �㡫�� - 楫�� ��� �஡��� ������⥫쭮� �᫮\n�� ����� 2,147,483,647\n\n-����� - ���� �� ���� ���祭��\n<-w> - ��� ᫮�\n<-s> - ��� ������\n<-p> - �� �.�. ��࠭��� (1800 ������)\n�᫨ �⮣� ��ࠬ��� ���, � �� 㬮�砭�� ��⠥��� <-s>\n�� ��⠫�� ���祭�� ��� ०��� - ���ࠢ����\n\n"
#define page 1800
/**/
void print2afdot()
{


}
void output(char *mode, double price, double count, double cost)
{
	printf(countof);
	switch(mode[1])
	{
	case 's':
		printf(simbols);
		printf("%.0f\n", count);
		printf(priceof, ofsimbol);
		break;
	case 'w':
		printf(words);
		printf("%.0f\n", count);
		printf(priceof, ofword);
		break;
	case 'p':
		printf(pages);
		if (((long long)(count * 100) % 100) != 0)
		{
			if (((long long)(count * 100) % 10) == 0)
			{
				printf("%.1f\n", count);
			}
			else
			{
				printf("%.2f\n", count);
			}
		}
		else
		{
			printf("%.0f\n", count);
		}
		printf(priceof, ofpage);
		break;
	}
	if (((long long)(price * 100) % 100) != 0)
	{
		if (((long long)(price * 100) % 10) == 0)
		{
			printf("%.1f\n", price);
		}
		else
		{
			printf("%.2f\n", price);
		}
	}
	else
	{
		printf("%.0f\n", price);
	}
	printf(priceof, oftext);
	if (((long long)(cost * 100) % 100) != 0)
	{
		if (((long long)(cost * 100) % 10) == 0)
		{
			printf("%.1f\n", cost);
		}
		else
		{
			printf("%.2f\n", cost);
		}
	}
	else
	{
		printf("%.0f\n", cost);
	}
	return;
}

double cntsmb(FILE *in)
{
	double count = 0;
	char c;
	while ((c = getc(in)) != EOF)
	{
		if (c != ' ' && c != '\n' && c != '\t')
		{
			count += 1.0;
		}
	}
	return count;
}

double cntwrd(FILE *in)
{
	char place = 0;
	double count = 0;
	char c;
	while ((c = getc(in)) != EOF)
	{
		if (c != ' ' && c != '\n' && c != '\t')
		{
			if (place == 0)
			{
				place = 1;
				count += 1.0;
			}
		}
		else
		{
			place = 0;
		}
	}
	return count;
}

double cntpg(FILE *in)
{
	return cntsmb(in) / page;
}


double readprice(char *lprice)
{
	int i;
	long long lenght;
	double k = 1;
	double price = 0;
	int dot = -1;
	int end;
	lenght = strlen(lprice);
	for (i = 0; i < lenght; i++)
	{
		if (lprice[i] == '.')
			{
				if (dot == -1)
				{
					dot = i;
				}
				else
				{
					return -1;
				}
			}
	}
	end = i;
	if(dot == -1)
		dot = end;
	for (i = dot - 1; i >= 0; i--)
	{
		if (lprice[i] >= '0' && lprice[i] <= '9')
		{
			price += (lprice[i] - '0') * k;
				k *= 10;
		}
		else
		{
			return -1;
		}
		if (price > (double)INT_MAX)
			return -1;
	}
	k = 0.1;
	for (i = dot + 1; i < end; i++)
	{
		if (lprice[i] >= '0' && lprice[i] <= '9')
		{
			price += (lprice[i] - '0') * k;
			k /= 10;
		}
		else
		{
			return -1;
		}
	}
	return price;
}

double readcount(FILE *in, char *s, double price)
{
	double count = -1;
	if ((strlen(s) == 2) && (s[0] == '-'))
	{
		switch (s[1])
		{
		case 's':
			count = cntsmb(in);
			break;
		case 'w':
			count = cntwrd(in);
			break;
		case 'p':
			count = cntpg(in);
			break;
		default:
			break;
		}
	}
	return count;
}

double calc(int arnum, char **arcc, double *count, double *price)
{
	FILE *in;
	if ((in = fopen(arcc[1], "r")) == 0)
		return -1;
	if ((*price = readprice(arcc[2])) == -1)
		return -2;
	if (arnum == 3)
	{
		if ((*count = readcount(in, "-s", *price)) == -1)
			return -3;
	}
	else
	{
		if((*count = readcount(in, arcc[3], *price)) == -1.0)
			return -3;
	}
	fclose(in);
	return (*price) * (*count);
}


void main(int argc, char *argv[])
{

	char mode[] = "-s";
	long long n;
	double cost, price, count;
	if (argc == 3 || argc == 4)
	{
		if (argc == 4)
		n = cost = calc(argc, argv, &count, &price);
		switch (n)
		{
		case -1:
			printf(codeopen, argv[1]);
			printf(codefull);
			break;
		case -2:
			printf(codeprice, argv[2]);
			printf(codefull);
			break;
		case -3:
			printf(codemode, argv[3]);
			printf(codefull);
			break;
		default:
			if (argc == 4)
			{
			mode[1] = argv[3][1];
			}
			output(mode, price, count, cost);
			break;
		}
	}
	else
	{
		printf(codearg, argc - 1);
		printf(codefull);
	}
	return;
}

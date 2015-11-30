#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "ctype.h"
int  chartoint(char simbol, int *dot, int i)
/*перевод в целочисленное представление из символьного
Получает символ цифры, указатель на позицию точки и номер читаемого символа
1Или возвращает значение цифры,
2Или записывает позицию точки в 'dot' и возвращает код нахождения точки
3Или возвращает код ошибки*/
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
	if (simbol == '.' && *dot == -1) /*запись позиции точки в "dot"*/
	{
		*dot = i;
		return -1;
	}
	return -2; /*вывод ошибки*/
}
char inttochar(int number)
/*перевод в символьное представление из целочисленного
Получает значение цифры
Возвращает символ цифры*/
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
/*заполнение массива числом получаемым на вход, нахождение точки "dot" и конца "end"
Получает массив со значениями цифр, основания систем счислений и указатель  на переменную для обозначения конца числа
1Возвращает точку или 2код ошибки*/
{
	int dot = -1; /*-1 на случай отсутствия точки*/
	getchar();
	char simbol = getchar();
	int i;
	for (i = 0; (simbol != 'EOF') && (simbol != '\n'); i++)
	{
		if ((number[i] = chartoint(simbol, &dot, i)) == -2 || number[i] >= b1) /*заполнение с проверкой ошибки*/
		{
			return 0;
		}
		simbol = getchar();
	}
	*end = i;/*позиция конца*/
	if (dot == -1) dot = i;
	return dot;
}
void printfloat(int *number, int lenght1, int lenght2)
/*печать
Получает массив со значениями цифр, позиции конца целой и дробной частей.
Печатает число посимвольно.*/
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
/*перевод из первой системы счисления во вторую.
Получает массив со значениями цифр, основания систем счислений, позиции точки и конца числа.
Возвращает возвращает массив со значениями цифр в целочисленном представлении, позиции конца целой и дробной частей*/
{
	int i;
	long long int Numb = number1[0];
	double Numbf, schet;
	/*целая часть*/
	for (i = 1; i < dot; i++) /*привод к десятичному числу*/
	{
		Numb = Numb*b1 + number1[i];
	}
	if (Numb == 0) /*проверка значения целой части*/
	{
		number2[0] = 0;
		*lenght1 = 1;
	}
	else
	{
		for (i = 0; Numb != 0; i++)/*перевод во вторую систему счисления*/
		{
			number2[i] = Numb%b2;
			Numb = Numb / b2;
		}
		*lenght1 = i;
	}
	/*дробная часть*/
	if (dot != end) /*Проверка наличия дробной части*/
	{
		Numbf = 0;
		for (i = end - 1; i > dot; i--) /*привод к десятичному числу*/
		{
			Numbf = (number1[i] + Numbf) / b1;
		}
		for (i = *lenght1; Numbf != 0 && i<*lenght1 + 12; i++) /*перевод во вторую систему счисления*/
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
	/*основания систем счислений, позиция точки, позиция конца, массив для первоночальных цифр, массив для переведённых цифр, позиция конца целой части, позиция конца дробной части*/
	scanf("%d %d", &b1, &b2);
	if (b1 > 1 && b2 > 1 && b1 < 17 && b2 < 17) /*проверка*/
	{
		dot = readfloat(number1, b1, b2, &end);/*чтение введённого числа*/
		if (dot && dot != (end - 1))/*проверка*/
		{
			b1tob2(number1, b1, b2, dot, end, &lenght1, &lenght2, number2);/*перевод*/
			printfloat(number2, lenght1, lenght2);/*печать*/
			return;
		}
	}
	printf("bad input");
	return;
}

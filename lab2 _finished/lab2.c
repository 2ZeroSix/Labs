#include <stdio.h>

/*чтение шаблона
получает массив для хранения шаблона "t"
считывает шаблон в "t"
возвращает либо
длину шаблона
код ошибки 0*/
int readtemplate(char *t)
{
	/*счётчик*/
	int i = 0;
	/*чтение шаблона*/
	while (((t[i] = getchar()) != '\n') && (i++ <= 16));
	/*проверка*/
	if (t[i] != '\n') return 0;
	t[i] = '\0';
	return i;
}

/*таблица стоп символов
получает массив с шаблоном "t", массив для таблицы стоп символов "ss", длину шаблона "lenght"
записывает таблицу стоп символов в "ss"*/
void stopsimbols(char *t, int *ss, int lenght)
{
	/*счётчик*/
	int i;
	/*заполнение максимальными значениями*/
	for (i = 0; i < 256; i++) ss[i] = lenght;
	/*заполнение для символов встречающихся в шаблоне*/
	for (i = 0; i < lenght - 1; i++)
	{
		ss[(unsigned char)t[i]] = lenght - i - 1;
	}
	return;
}

/*чтение строки в буфер
получает массив буфера "s", смещение "nlenght", длину шаблона "lenght", кол-во считанных символов "sum"
считывает новые символы в буфер по модулю длины шаблона
0 конец строки
1 удачное считывание*/
int readstring(char *s, int nlenght, int lenght, int *sum)
{
	/*счётчик*/
	int i;
	/*чтение*/
	for (i = *sum; i < *sum + nlenght; i++)
	{
		s[i % lenght] = getchar();
	}
	/*проверка на конец строки*/
	if (s[(i - 1) % lenght] == EOF) return 0;
	/*увеличение кол-ва считанных символов до нынешнего*/
	*sum += nlenght;
	return 1;
}

/*Вывод протокола работы алгоритма Бойера-Мура
получает массив с шаблоном "t", длину шаблона "lenght"
выводит протокол*/
void BMsearch(char *t, int lenght)
{
	/*буфер*/
	char s[17];
	/*кол-во прочитанных символов*/
	int sum = 0;
	/*счётчик*/
	int i;
	/*смещение + счётчик*/
	int nlenght = lenght;
	/*таблица стоп символов*/
	int ss[256];
	/*заполнение таблицы стоп символов*/
	stopsimbols(t, ss, lenght);
	/*чтение строки и вывод протокола*/
	while ((readstring(s, nlenght, lenght, &sum)))
	{
		i = lenght - 1;
		nlenght = sum - 1;
		while ((i >= 0) && (t[i] == s[nlenght-- % lenght]))
		{
			printf(" %d", sum + i-- - lenght + 1);
		}
		if (i >= 0) printf(" %d", sum +  i - lenght + 1);
		nlenght = ss[(unsigned char)s[(sum - 1) % lenght]];
	}
	return;
}

void main()
{
	/*шаблон*/
	char t[17];
	/*длина шаблона*/
	int lenght;
	/*чтение шаблона, нахождение длины и запуск алгоритма*/
	if (lenght = readtemplate(t))
	{
		BMsearch(t, lenght);
	}
	return;
}

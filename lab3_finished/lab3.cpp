#include <stdio.h>

#define tl  17 /*максимальная длина шаблона*/
#define d  256 /*Длина алфавита*/
/*чтение шаблона*/
int readtemplate(char *t)
{
	int i = 0;
	while (((t[i] = getchar()) != '\n') && (i++ < tl));
	if (t[i] != '\n') return 0;
	t[i] = '\0';
	return i;
}
/*заполнение буфера
Получает указатель на буфер, длину шаблона и номер символа, на которм остановилось считывание
возвращает коды
0 код конца строки
1 код успешного считывания*/
int readstring(char *s, int l, int nl, int *sum)
{
	int i;
	for (i = *sum; i< *sum + nl; i++)
	{
		if ((s[i % l] = getchar()) == EOF)
			return 0;
	}
	*sum += nl;
	return 1;
}
/*Печать протокола алгоритма Рабина-Карпа
получает массив с шаблоном и его длину*/
void RK_search(char *t, int l)
{
	// массив буфера
	char s[tl];
	// хэш шаблона, хеш строки, счётчик, степень, кол-во считанных символов
	int t_t, t_s, i, h = 1, sum = 0;
		t_t = 0;
		t_s = 0;
		for (i = 0; i < l; i++)
		{
			t_t += ((unsigned char)t[i] % 3) * h;
			h *= 3;
		}
		printf("%d", t_t);
		if (readstring(s, l, l, &sum))
		{
			h = 1;
			for (i = 0; i < l; i++)
			{
				t_s += ((unsigned char)s[i] % 3) * h;
				h *= 3;
			}
		while (1)
		{
			if (t_t == t_s)
			{
				for (i = 0; (i < l) && ((unsigned char)t[i] == (unsigned char)s[(sum + i) % l]); i++)
					printf(" %d", sum - l + i + 1);
				if (i != l)
					printf(" %d", sum - l + i + 1);
			}
			t_s -= ((unsigned char)s[sum % l]) % 3;
			if (readstring(s, l, 1, &sum))
			{
				t_s = (t_s + ((unsigned char)s[(sum - 1) % l] % 3) * h) / 3;
			}
			else
			{
				return;
			}
		}
	}
	return;
}

void main()
{
	/*длина шаблона*/
	int lenght;
	/*массив шаблона*/
	char templat[tl];
	if (lenght = readtemplate(templat))
	{
		RK_search(templat, lenght);
	}
	return;
}

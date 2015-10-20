#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#define codez printf("division by zero");
#define codes printf("syntax error");
/*
Подсчёт по знаку
Получает
-два числа <arg1>, <arg2>
-знак между ними <expr>
В случае успеха
-Возвращает
--Значение выражения
В случае деления на ноль
-Возвращает
--<0>
-Изменяет
--меняет expr на '0'*/
long long calcexpr(long long arg1, long long arg2, char expr)
{
  switch(expr)
  {
    case '*':
      return arg1 * arg2;
    case '+':
      return arg1 + arg2;
    case '-':
      return arg1 - arg2;
    case '/':
      if (arg2 != 0)
        return arg1 / arg2;
      else
      {
        expr = '0';
        return 0;
      }
  }
}
/*
Перевод из целочисленного представления в символьный
Получает
-число <arg>
-строку <*args>
Изменяет
-записывает в <*args> число в символьном представлении
*/
void lltostr(long long arg, char *args)
{
  int i = 0, j;
  char c;
  while (arg > 0)
  {
    args[i++] = arg % 10 + '0';
    arg /= 10;
  }
  args[i] = '\0'
  for (j = 0; j < i / 2; j++)
  {
    c = arg[j];
    arg[j] = arg[i - j - 1];
    arg[i - j - 1] = c;
  }
  return;
}
/*
Перевод из символьного представления в целочисленное
Получает
-строку <*args>
-число <*arg>
Изменяет
-записывает в <*arg> число в целочисленном представлении
*/
void strtoll(char *args,long long *arg)
{
  *arg = 0;
  int i;
  while(args[i] != '\0')
  {
    *arg = *arg * 10 + args[i++] - '0';
  }
  return;
}
/*
Калькулятор скобок
Получает
-массив со всем выражением <*s>
-длину массива <l>
-положение последней открывающей скобки
-положение закрывающей скобки
Изменяет
-в строке <*s> заменяет скобки с выражением внутри них на целое число
*/
void calcbrackets(char *s, l, cso, csc)
{
  /*счётчики*/ 
  int i, j = 0, k = 0, expr;
  /*элемент в виде строки*/
  char argc[20];
  /*последний и предпоследний элементы*/
  long long arg1, arg2;
  for(i = 0; i < csc - cso; i++)
  {

      if (k == 0)
    {
      k = 1;
      if (s[i] == '-')
        argcp[j++] = s[i];
    }
    else
    {
      if ((s[i] >= '0') && (s[i] <= '9'))
      {
        argc[j++] = s[i];
      }
      else
      {
        expr = s[i];
        argc[j] = '\0'
        j = 0;
        strtoll(argc, &arg1);
        while ((s[i] >= '0') && (s[i] <='9')
          argc[j++] = s[i++];
          argc[j] = '\0';
          strtoll(argc, &arg2);
          arg1 = calcexpr(arg1, arg2, expr);
      }
    }
  }
}
/*
Калькулятор
Получает
-строку с выражением <*s>
-длину строки <l>
-указатель на переменную под результат <*result>
В случае удачного расчёта
-Возвращает
--<1>
-Изменяет
--result = результат расчёта;
В случае  деления на 0
-Возвращает
--<0>
*/
int fullcalc(char *s, int l, int *result)
{
  /*массив с позициями открывающих скобок*/
  int cso[499];
  /*позиция последней закрывающей скобки*/
  int csc;
  /*счётчики*/
  int i, so = 0;
  for (i = 0; i < l; i++)
  {
    if (s[i] == '(')
      cso[so++] = i;
    if (s[i] == ')')
      {
        csc = i;
        calcbrackets(s, cso[--so], csc);
      }
  }
}
/*
проверка символа
Получает
-символ
-указатель на переменную с кол-вом открывающих скобок
-указатель на переменную с кол-вом закрывающих скобок
-указатель на переменную с позицией последней открывающей скобки
-указатель на переменную с позицией последней закрывающей скобки
-указатель на переменную с позицией последнего знака действия
Возвращает
-код 0 в случае недопустимого символа
-код 1 в случае допустимого символа
*/
int checksimb(char c, int *so, int *sc, int *cso, int *csc, int *zn)
{
  if (((c >= '0') && (c <= '9'))||(c == '(')||(c == ')')||(c == '*')||(c == '/')||(c == '+')||(c == '-'))
    {
      if((c == '*') || (c == '/') || (c == '-') || (c == '+'))
        {
          if (*zn == i - 1)
            return 0;
          *zn = i;
        }
      if(c == '(')
        {
          if(*csc == i - 1)
            return 0;
          *cso = i;
          *so++;
        }
      if(c == ')')
        {
          if(*cso == i - 1)
            return 0;
          *csc = i;
          *sc++;
        }
      if (so>=sc)
        return 1;
    }
  return 0;
}
/*
Считывание выражения
Получает
-строку <s>
Изменения
-заполняет строку
Возвращает
-код 0 в случае недопустимости
-длина в случае допустимости
*/
int fillscalc(char *s,)
{
  /*счётчик*/
  int i = 1;
  /*
  -кол-во открывающих скобок
  -кол-во закрывающих скобок
  */
  int so = 0, sc = 0;
  /*
  -позиция последний открывающей скобки
  -позиция последней закрывающей скобки
  -позиция последнего знака действия
  */
  int cso = -1, csc = -1, zn = -1;
  s[0] = '(';
  while(((s[i] = getchar()) != EOF) && checksimb(s[i], so, sc, cso, csc, zn) && (i < 1002))
    i++;
  if ((s[i]!=EOF)||(so!=sc)
    return 0;
  s[i] = ')';
  return i + 1;
}

void main()
{
  /*строка с выражением*/
  char *scalc[1002];
  /*длина выражения*/
  int l;
  /*значение выражения*/
  long long result;
  if(l = fillscalc(scalc))
  {
    if(result = fullcalc(scalc, l))
    {
      printf("%lld", result);
    }
    else
    {
      codez
    }
  }
  else
  {
    codes
  }
  return;
}

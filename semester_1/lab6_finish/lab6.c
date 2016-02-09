#include <stdio.h>
#include <stdlib.h>
/*
меняет значения 2 эелементов между собой
получает
-указатели на элементы <a1>, <a2>
*/
void swapint(int *a1, int *a2)
{
  /*переменная для замены*/
  int k;
  k = *a1;
  *a1 = *a2;
  *a2 = k;
  return;
}
/*
вывод решения на экран
получает
-кол-во элементов <N>
-массив с элементами <arr>
*/
void output(int N, int *arr)
{
  /*счётчик*/
  int i;
  for (i = 0; i < N; i++)
    printf("%d ", arr[i]);
  printf("\n");
  return;
}
/*
Быстрая сортировка
получает
-сортируемый массив <a>
-левую границу отсортированного <l>
-правую границу отсортированного <r>
изменяет
-сортирует <*a>
*/
void qusort(int *a, int l, int r)
{
  /*
  -центральный элемент
  -счётчик для левой части
  -счётчик для правой части
  */
  int x, i, j;
  i = l;
  j = r;
  x = a[(l+r)/2];
  do
  {
    while(a[i]<x)
      i++;
    while(x<a[j])
      j--;
    if(i <= j)
    {
      swapint(&a[i++], &a[j--]);
    }
  } while(i < j);
  if (l < j)
    qusort(a, l, j);
  if (l < r)
    qusort(a, i, r);
    return;
}


void main()
{
  /*
  -счётчик
  -кол-во элементов
  -сортируемый массив
  */
  int i, N, *arr;
  /*
  Чтение входных данных
  */
  scanf_s("%d", &N, sizeof(int));
  arr = (int*) calloc(N + 1, sizeof(int));
  for(i = 0; i < N; i++)
  {
    scanf_s("%d", &arr[i], sizeof(int));
  }
  /*
  Запуск сортировки
  */
  qusort(arr, 0, N - 1);
  /*
  Вывод решения
  */
  output(N, arr);
  return;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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
меняет значения 2 эелементов между собой
получает
-указатели на элементы <a1>, <a2>
изменяет
-меняет местами значения <*a1> и <*a2>
*/
void swapint(int *a1, int *a2)
{
  int k;
  k = *a1;
  *a1 = *a2;
  *a2 = k;
  return;
}
/*
построение пирамиды
получает
-массив <h>
-номер первого <i> элемента из образующих пирамиды
-последнего <n> элемента из образующих пирамиды
*/
void sift(int *h, int i, int n)
{
  int r , l, k;
  i++;
  while((l = i * 2) <= n)
  {
    r = ((l + 1) <= n)? l + 1 : i;
    if(h[i - 1]>=h[l - 1] && h[i - 1] >= h[r - 1])
      return;
    k = (h[l- 1] >= h[r - 1])? l : r;
    swapint(&h[i - 1], &h[k - 1]);
    i = k;
  }
  return;
}


void main()
{
  /*
  -счётчик
  -кол-во элементов
  -массив для элементов*/
  int i, N, *arr;
  /*
  Чтение входных данных
  */
  scanf("%d", &N);
  arr = (int*)calloc(N,sizeof(int));
  for(i = 0; i < N; i++)
  {
    scanf("%d", &arr[i]);
  }
  /*
  Подготовка
  */
  for (i = N / 2; i >= 0; i--)
    sift(arr, i, N);
  /*
  Сортировка
  */
  for (i =  N - 1; i > 0; i--)
  {
    swapint(&arr[0], &arr[i]);
    sift(arr, 0, i);
  }
  /*
  Вывод решения
  */
  output(N, arr);
  free(arr);
  return;
}
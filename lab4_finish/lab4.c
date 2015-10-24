#include <stdio.h>
int readl(int *p)
{
  int w[10] = {0};
  int i = 0;
  char c;
  while((c = getchar()) != '\n')
  {
    if (c >= '0' && c <= '9' && w[c - '0']++ == 0)
    {
      p[i++] = c - '0';
    }
    else
    {
      return 0;
    }
  }
  return i;
}

int printp(int *p, int lp)
{
  int i, j;
  int buf = 10, bufn;
  for (i = lp - 1; i > 0; i--)
  {
    if (p[i] > p[i - 1])
      break;
  }
  if (i == 0)
    return 0;
  i--;
  for (j = i + 1; j < lp; j++)
  {
    if (p[j] > p[i] && p[j] < buf)
    {
      buf = p[j];
      bufn = j;
    }
  }
  p[bufn] = p[i];
  p[i] = buf;
  for (j = 0; j < (lp - i) / 2; j++)
  {
    buf =  p[i + 1 + j];
    p[i + j + 1] = p[lp - 1 -j];
    p[lp - 1 - j] = buf;
  }
  for(i = 0; i < lp; i++)
    printf("%d", p[i]);
    printf("\n");
  return 1;
}

void main()
{
  int i;
  /*перестановка*/
  int p [10];
  /*кол-во перестановок*/
  int n;
  /*длина перестановки*/
  int lp;
  if(lp = readl(p))
  {
    scanf_s("%d", &n, sizeof(int));
    for (i = 0; i < n && printp(p, lp); i++);
  }
  else
  {
    printf("bad input");
  }
  return;
}

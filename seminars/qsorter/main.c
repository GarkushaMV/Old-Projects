#include <stdio.h>
#include <stdlib.h>

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main()
{
    int  n, i = 0;                                         //number of elements
    scanf ("%d", &n);
    int *a = malloc( (sizeof(int) * n) );
    for (; i < n; i++)
        scanf ("%d", &( a[i] ));
    qsort ( a, n, sizeof(int), compare);
    for (i = 0; i < n; i++)
        printf ("%d ", a[i]);
    return 0;
}

#include <stdio.h>
#include <assert.h>

int main()
{
    int** a;
    int N,                                                      //matrix size
            counter_1, counter_2;                               //counters
    scanf("%d", &N);

    a=new int*[N];                                             //initializing malloc
    for(counter_1 = 0; counter_1 < N; ++counter_1)
    {
        a[counter_1]=new int[N];

        for(counter_2 = 0; counter_2 < N; ++counter_2)
                a[counter_1][counter_2]=0;
    }

    printf("\n\n\n");                                          //making output readable

    for(counter_1 = 0; counter_1 < N; ++counter_1)             //I'm usung preincrement, because I can =)
        for(counter_2 = 0; counter_2 < N; ++counter_2)
                scanf("%d", &a[counter_1][counter_2]);

    for(counter_1 = 0; counter_1 < N; ++counter_1)             //and just swap counter_1 and counter_2
    {
        for(counter_2 = 0; counter_2 < N; ++counter_2)
                printf("%d ", a[counter_2][counter_1]);
        printf("\n");
    }

    return 0;                                                  //and it's ready
}
//I don't know where to use here functions and asserts

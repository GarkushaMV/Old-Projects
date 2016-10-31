#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int task1()
{
    return 0;
}

int main()
{
    char input[2];
    scanf("%c", &input[0]);
    switch(input[0])
    {
    case '1':
        {
            scanf("%c", &input[1]);
            printf("%c", input[1]);
            break;
        }
    case '2':
        {
            printf("ololo");
            break;
        }
    default:
        {
            assert(0);
        }
    }
    return 0;
}

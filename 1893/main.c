#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    int i;
    scanf("%c", &c);
    i=c-'1'+1;
    scanf("%c", &c);
    if(c>='0' && c<='9')
    {
        i=i*10+c-'0';
        scanf("%c", &c);
    }
    if(i<3)
    {
        if(c=='A' || c=='D')
            printf("window");
        else
            printf("aisle");
    }
    else
    {
        if(i<21)
        {
            if(c=='A' || c=='F')
                printf("window");
            else
                printf("aisle");
        }
        else
        {
            if(c=='A' || c=='K')
                printf("window");
            else
            {
                if(c=='C' || c=='D' || c=='G' || c=='H')
                    printf("aisle");
                else
                    printf("neither");
            }
        }
    }
    return 0;
}

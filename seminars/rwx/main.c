#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[3];
    scanf ("%c%c%c", &(a[0]), &(a[1]), &(a[2]));
    int i = 0;
    for(; i < 3; i++)
    {
        a[i]-='0';
        if( a[i]/4 == 1 )
            printf ( "r" );
        else
            printf ( "-" );
        a[i] %= 4;
        if( a[i]/2 == 1 )
            printf ( "w" );
        else
            printf ( "-" );

        if( a[i]%2 == 1 )
            printf ( "x" );
        else
            printf ( "-" );
    }
    return 0;
}

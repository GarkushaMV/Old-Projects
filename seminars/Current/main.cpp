#include <stdio.h>
#include <stdlib.h>

char* str;
int i;

void check (char *c)
{
    if(*c >= 'a' && *c <= 'z')
        *c += 'a' - 'A';
}

void doublecheck (char *c)
{
    if(*c == str[0])
        *c = 255;
}

int main()
{
    str = (char*) calloc ( 100, sizeof(char) );
    for(i = 0; i <= 100; i++)
    {
        scanf("%c", &str[i]);
        if(str[i] == 0)
            break;
    }
    printf("%s\n", str);
    if(str[100] != 0 || str[3] != 0) //made by calloc() NULL
        exit(3);
    check( &str[0] );
    for(i = 1; i <= 100; i++)
    {
        check(&str[i]);
        doublecheck(&str[i]);
    }
    printf("%s", str);
}


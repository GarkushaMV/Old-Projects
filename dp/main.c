#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, cr, r[10];  /*объявляем "бегунка", нынешнее число и массив для максимумов*/
    char c, o[11];
    for(i=0; i<10; i++)
        o[i]='0'+1;
    0[10]=' ';
    for(i=0; i<10; i++)
    {
        c=o[(rand()%10)];
        printf("%c", c);
        r[i]=(c-'0');
        cr=r[i];
            while(c>'0' && c<='9') /*описывает конец строки*/
        {
            cr=(cr%10)*10+(c-'0');
            if(cr>r[i])
                r[i]=cr;
            c=o[(rand()%11)];
            printf("%c", c);
        }
    }
    for(i=0; i<10; i++)
        printf("%d", r[i]);
    return 0;
}

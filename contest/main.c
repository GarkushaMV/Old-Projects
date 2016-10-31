char* convert (const char* str)
{
    int i = 0, j = 0;
    while (str[i]!='\0')
        i++;
    j = (i+2)/3+1;
    char* a = (char*) calloc ( j , sizeof(char) );
    a[j]='\0';
    for (i--, j--; i>=0; i-=3, j--)
    {
        if(i >= 2)
        {
            if(str[i-2] == '1')
            {
                if(str[i-1] == '1')
                {
                    if(str[i] == '1')
                        a[j]=7;
                    else
                        a[j]=6;
                }
                else
                {
                    if(str[i] == '1')
                        a[j]=5;
                    else
                        a[j]=4;
                }
            }
            else
            {
                if(str[i-1] == '1')
                {
                    if(str[i] == '1')
                        a[j]=3;
                    else
                        a[j]=2;
                }
                else
                {
                    if(str[i] == '1')
                        a[j]=1;
                    else
                        a[j]=0;
                }
            }
        }
        else
        {
            if(i >= 1)
            {
                if(str[i-1] == '1')
                {
                    if(str[i] == '1')
                        a[j]=3;
                    else
                        a[j]=2;
                }
                else
                {
                    if(str[i])
                        a[j]=1;
                    else
                        a[j]=0;
                }
            }
            else
                a[i] = str[i];
        }
    }
    return a;
}

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int numberota(int i, int j)
{
    int k=0;
    if(i>2)
    {
        if(j>2)
        {
            k+=27;
            if(j==4 && i==4)
                k+=8;
            else
            {
                if(i==5)
                {
                    k+=(5-j);
                }
                else
                {
                    if(i==3)
                    {
                        k+=(j+1);
                    }
                    else
                    {
                        if(j==3)
                        {
                            k+=3;
                        }
                        else
                        {
                            k+=7;
                        }
                    }
                }
            }
        }
        else
        {
            k+=18;
            if(j==1 && i==4)
                k+=8;
            else
            {
                if(j==0)
                {
                    k+=(5-i);
                }
                else
                {
                    if(j==2)
                    {
                        k+=(i+1);
                    }
                    else
                    {
                        if(i==3)
                        {
                            k+=3;
                        }
                        else
                        {
                            k+=7;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(j>2)
        {
            if(i==1 && j==4)
                k+=8;
            else
            {
                if(i==0)
                {
                    k+=(5-j);
                }
                else
                {
                    if(i==2)
                    {
                        k+=(j+1);
                    }
                    else
                    {
                        if(j==3)
                        {
                            k+=3;
                        }
                        else
                        {
                            k+=7;
                        }
                    }
                }
            }
        }
        else
        {
            k+=9;
            if(j==1 && i==1)
                k+=8;
            else
            {
                if(j==0)
                {
                     k+=i;
                }
                else
                {
                    if(j==2)
                    {
                        k+=(6-i);
                    }
                    else
                    {
                        if(i==2)
                        {
                            k+=3;
                        }
                        else
                        {
                            k+=7;
                        }
                    }
                }
            }
        }
    }
    k++;
    return k;
}

/*int sfbawsuwk ()
{
    for(i=0;i<9;i++)
        if (a[i]>a[i+1]) {
            a[i]=kotiki;
            a[i]=a[i+1];
            a[i+1]=kotiki;
            i=0;
        }

}*/

int main()
{
    int a[36];
    int ti=time(NULL);
    for(int i=0; i<36; i++)
    {
        srand(ti);
        a[i]=(rand()%80-40);
        ti++;
    }
    for(int i=0; i<36; i++)
        {
            cout << a[i] << " ";
            }
    cout << "\n\n";
    int b[6][6];
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            b[i][j]=a[numberota(i, j)];
    for(int i=0; i<6; i++)
        {
            for(int j=0; j<6; j++)
                {
                    cout.fill(' ');
    cout.width(5);
    cout << b[i][j] << " ";}
            cout << "\n";
        }
    for(int kotiki, k=0; k<30; k+=9)
        for(int i=0;i<8;i++)
            if (a[k+i]>a[k+i+1])
            {
                kotiki=a[k+i];
                a[k+i]=a[k+i+1];
                a[k+i+1]=kotiki;
                i=0;
            }
    cout << "\n";
    for(int i=0; i<6; i++)
        for(int j=0; j<6; j++)
            b[i][j]=a[numberota(i, j)];
    for(int i=0; i<6; i++)
        {
            for(int j=0; j<6; j++)
                {
                    cout.fill(' ');
    cout.width(5);
    cout << b[i][j] << " ";}
            cout << "\n";
        }
    return 0;
}

#include <iostream>

using namespace std;

int main()
{
    int n, i;
    cin >> n;
    n++;
    int** a;
    a=new int*[n];
    for(i=0; i<n; i++)
        a[i]=new int[n];
    a[0][0]=1;
    for(i=0; i<n; i++)
        a[0][i]=0;
    for(i=1; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(j>i)
                a[i][j]=0;
            else
            {

                if(i==j || j==1)
                    a[i][j]=1;
                else
                {
                    if(j==0)
                        a[i][j]=0;
                    else
                        a[i][j]=a[i-j][j]+a[i-1][j-1];

                }
            }
        }
        n--;
    for(i=0; i<n; i++)
        a[n][n]+=a[n][i];
    cout << a[n][n];
}

#include <iostream>

using namespace std;

int main()
{
    int a[7];
    for(int i=0; i<7; i++)
        cin >> a[i];
    if(!(((1+a[0]+a[1]+a[3]+a[6])%2)&&((1+a[0]+a[2]+a[3]+a[5])%2)&&((1+a[1]+a[2]+a[3]+a[4])%2)))
    {
        a[0]=1-a[0];
        for(int i=1;i<7; i++)
        {
            if(((1+a[0]+a[1]+a[3]+a[6])%2)&&((1+a[0]+a[2]+a[3]+a[5])%2)&&((1+a[1]+a[2]+a[3]+a[4])%2))
                i=7;
            else
            {
                a[i-1]=1-a[i-1];
                a[i]=1-a[i];
            }
        }
    }
    for(int i=0; i<7; i++)
        cout << a[i] << ' ';
    return 0;
}

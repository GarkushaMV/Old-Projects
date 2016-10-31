#include <iostream>

using namespace std;

int main()
{
    signed int a[6];
    unsigned int n, i;
    bool b;
    cin >> n;
    n--;
    a[0]=n;
    for(i=5; i>0; i--)
    {
        a[i]=a[0]%10;
        a[0]=a[0]/10;
    }
    a[0]=a[0]+a[1]+a[2]-a[3]-a[4]-a[5];
    b=(a[0]==0);
    n=n+2;
    a[0]=n;
    for(i=5; i>0; i--)
    {
        a[i]=a[0]%10;
        a[0]=a[0]/10;
    }
    a[0]=a[0]+a[1]+a[2]-a[3]-a[4]-a[5];
    b=((a[0]==0) || b);
    if(b)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}

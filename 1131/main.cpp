#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long n, k, m=1;
    cin >> n >> k;
    long i;
    for(i=0; n>m && m<k; i++)
        m=m<<1;
    if(n<=m)
        cout << i;
    else
    {
        i+=(n-m)/k +((n-m)%k!=0);
        cout << i;
    }
}

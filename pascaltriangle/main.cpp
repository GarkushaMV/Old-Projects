#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    n++;
    int a[n][n];
    for(int i=0; i<n; i++)
    {
        a[i][0]=1;
        for(int j=1; j<i; j++)
            a[i][j]=(a[i-1][j-1]+a[i-1][j]);
        a[i][i]=1;
    }
    n--;
    for(int i=0; i<=n; i++)
        cout << a[n][i] << ' ';
    return 0;
}

#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int a[n];
    int i;
    for(i=0; i<n; i++)
        a[i]=0;
    for(int j=0; j<m; j++)
    {
        cin >> i;
        a[i-1]++;
    }
    double t;
    for(i=0; i<n; i++)
    {
        t=m;
        t=(100*a[i])/t;
        cout.precision(2);
        cout << fixed << t << "% \n";
    }
    return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int a[10];
    vector<long double> c1(20);
    vector<long double> c2(20);
    long double b[10];
    a[0]=1; a[1]=1;
    for(int i=2; i<10; i++)
        a[i]=a[i-1]+a[i-2];
    b[0]=1;
    b[1]=1;
    long long fak=2;
    long long deg;
    for(int i=3; i<=10; i++)
    {
        deg=i;
        for(int j=2; j<i; j++)
            deg*=i;
        b[i-1]=(b[i-2]+b[i-3])*deg/fak;
        fak*=i;
    }
    for(int i=0; i<20; i+=2)
        c1[i]=a[(i/2)];
    for(int i=1; i<20; i+=2)
        c1[i]=b[(i/2)];
    c2=c1;
    sort(c2.begin(), c2.end());
    cout.setf(ios::fixed);
    for(int i=0; i<10; i++)
        cout << a[i]<< " ";
    cout << "\n";
    for(int i=0; i<10; i++)
        cout << b[i] << " ";
    cout << "\n";
    for(int i=0; i<20; i++)
        cout << c1[i] << " ";
    cout << "\n";
    for(int i=0; i<20; i++)
        cout << c2[i] << " ";
    cout << "\n";
}

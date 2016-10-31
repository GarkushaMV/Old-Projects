#include <iostream>

using namespace std;

int main()
{
    int p1, p2;
    cin >> p1 >> p2;
    int a1, a2;
    a1=p1;
    a2=p2;
    while(a1>0 && a2>0)
    {
        if(a1>a2)
            a1%=a2;
        else
            a2%=a1;
    }
    a1=max(a1, a2);
    for(int i=1; i<p2; i++)
        if(i%a1!=0)
    {
        p1=0;
        cout << i << ' ';
    }
    if(p1!=0)
        cout << "-1";
}

#include <iostream>

using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    b=2*b+40;
    a=2*a+39;
    if(a>b)
        cout << a;
    else
        cout << b;
    return 0;
}

#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int x, y, k=1;
    cin >> x;
    for(int i=1; i<n; i++)
    {
        cin >> y;
        if(x==y)
            k++;
        else
        {
            cout << k <<' ' << x << ' ';
            x=y;
            k=1;
        }
    }
    cout << k <<' ' << x << ' ';
    return 0;
}

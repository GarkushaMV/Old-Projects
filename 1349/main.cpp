#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    switch(n)
    {
    case 1:
    {
        cout << "1 2 3";
        break;
    }
    case 2:
    {
        cout << "3 4 5";
        break;
    }
    default:
    {
        cout << "-1";
        break;
    }
    }
    return 0;
}

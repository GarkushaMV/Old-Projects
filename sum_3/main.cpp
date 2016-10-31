#include <iostream>

using namespace std;

int main()
{
    int k;
    cin >> k;
    k--;
    cout.fill('0');
    cout.width(2);
    cout << (8+(k*50+45)/60);
    cout << ':' ;
    cout.fill('0');
    cout.width(2);
    cout << ((k*50+45)%60);
    return 0;
}

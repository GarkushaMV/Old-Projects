#include <iostream>

using namespace std;

int main()
{
    int j;
    char c;
    cin >> c;
    j=(c-'0')%7;
    while(cin >> c)
        j=(j*3+(c-'0'))%7;
    cout << j;
}

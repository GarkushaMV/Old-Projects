#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    string s;
    getline(cin, s);
    /*char j = 22;
    for(int i = 0; s[i] != 0; i++)
        if(s[i] >= 'A' && s[i] <= 'Z')
            cout << char((s[i]+j)%'Z' + 'A'*floor((s[i]+j)/'Z'));
        else
            cout << s[i];
    */
    for(int i = 0; s[i] != 0; i++)
        if(s[i] >= 'A' && s[i] <= 'Z')
            cout << char('Z' - s[i] + 'A');
    else
            cout << s[i];
    return 0;
}

#include <iostream>

using namespace std;

typedef pair<char, char> ie;
int main()
{
    int sz;
    cin >> sz;
    ie s[sz];
    for(int i=0; i<sz; i++)
        cin >> s[i].first >> s[i].second;
    char k;
    cin >> k;
    for(int i=0; i<sz; i++)
        if(s[i].first==k)
            cout << s[i].first << s[i].second << endl;
    return 0;
}

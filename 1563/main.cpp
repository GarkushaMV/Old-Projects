#include <iostream>
#include <set>

using namespace std;

int main()
{
    int n;
    cin >> n;
    set<string> s;
    string c;
    getline(cin, c);
    for(int i=0; i<n; i++)
    {
        getline(cin, c);
        s.insert(c);
    }
    cout << (n-s.size());
    return 0;
}

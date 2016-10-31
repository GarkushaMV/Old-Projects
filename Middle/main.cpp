#include <iostream>
#include <set>
#include <iterator>

using namespace std;

int main()
{
    multiset<int> s;
    int in;
    int n;
    cin >> n;
    for(int i=0; i<n; i++)
    {
        cin >> in;
        s.insert(in);
    }
    long double l=0;
    char b[30][30];
    for(int i=0; i<30; i++)
        for(int j=0; j<30; j++)
            b[i][j]=' ';
    int i=0;
    while(!s.empty())
    {
        l+=*(s.begin());
        b[i][(*(s.begin())-55)]='*';
        s.erase(s.begin());
        i++;
    }
    l=l/n;
    cout << l << "\n";
    for(i=0; i<30; i++)
    {
        for(int j=0; j<30; j++)
            cout << b[j][i];
        cout << "\n";
    }
}

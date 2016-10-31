#include <iostream>
#include <set>

using namespace std;

int main()
{
    int n;
    cout << "enter size\n";
    cin >> n;
    int g, d[n];
    multiset<int> l, r;
    cout << "enter matrix\n";
    int j;
    for(int i=0; i<n; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            cin >> g;
            l.insert(g);
        }
        cin >> d[i];
        for(j++; j<n; j++)
        {
            cin >> g;
            r.insert(g);
        }
    }
    multiset<int>::iterator L=l.begin(), R=r.begin();
    for(int i=0; i<n; i++)
    {
        for(j=0; j<n-i-1; j++, L++)
            cout << (*L) << " ";
        cout << d[i] << " ";
        for(j++; j<n; j++, R++)
            cout << (*R) << " ";
            cout << "\n";
    }
}

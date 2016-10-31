#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cout << "insert n and m\n";
    cin >> n >> m;
    int g;
    vector < vector <int> > a(n);
    for(int i=0; i<n; i++)
    {
        cout << "insert " << (i+1) << " line\n";
        for(int j=0; j<m; j++)
        {
            cin >> g;
            a[i].push_back(g);
        }
    }
    cout << "your malloc\n";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    for(int i=0; i<n; i++)
        sort(a[i].begin(), a[i].end());
    cout << "your sorted malloc\n";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    return 0;
}

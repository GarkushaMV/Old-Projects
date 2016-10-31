#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
    int d1, d2, n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a[0] >> d1 >> b[0] >> d2;
    d1-=a[0];
    d2-=b[0];
    for(int i=1; i<n; i++)
    {
        a[i]=a[i-1]+d1;
        b[i]=b[i-1]+d2;
    }
    set<int> c;
    c.insert(a.begin(), a.end());
    c.insert(b.begin(), b.end());
    cout << (2*n-c.size());
    return 0;
}

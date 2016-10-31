#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int n;
    cin >> n;
    long double l, s=0;
    for(int i=0; i<n; i++)
    {
        cin >> l;
        s+=(l/n);
    }
    cout << setprecision( 6 ) << fixed << s;
    return 0;
}

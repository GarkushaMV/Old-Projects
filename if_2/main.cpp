#include <iostream>

using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    cout << min(min(n, m), k);
    return 0;
}

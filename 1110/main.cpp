#include <iostream>

using namespace std;

int main()
{
    int n, m, y;
    bool f=0;
    cin >> n >> m >> y;
    int c=1;
    for(int i=1; i<m; i++)
    {
        c=i;
        for(int j=1; j<n; j++)
            c=(i*c)%m;
        if(c==y)
        {
            cout << i << ' ';
            f=1;
        }
    }
    if(!f)
        cout << "-1";
    return 0;
}

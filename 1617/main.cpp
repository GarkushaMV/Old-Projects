#include <iostream>
#include <map>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int k, c=0;
    map <int, char> m;
    while(n>0)
    {
        n--;
        cin >> k;
        m[k]++;
        if(m[k]==4)
        {
            m[k]=0;
            c++;
        }
    }
    cout << c;
    return 0;
}

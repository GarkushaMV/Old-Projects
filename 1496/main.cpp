#include <iostream>
#include <string>
#include <map>
#include <iterator>

using namespace std;

typedef map <string, int> mp;

int main()
{
    int sz;
    cin >> sz;
    mp m;
    string in;
    for(int i=0; i<sz; i++)
    {
        cin >> in;
        m[in]++;
    }
    for (mp ::iterator  it=m.begin();it!=m.end();it++)
        if((*it).second>1)
            cout << (*it).first << endl;
    return 0;
}

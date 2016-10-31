#include <iostream>
#include <set>

using namespace std;

int main()
{
    int st, pr, in;
    cin >> st;
    multiset<int> su;
    for(int i=0; i<st; i++)
    {
        cin >> in;
        su.insert(in);
    }
    set<int> pe;
    st=0;
    cin >> pr;
    for(int i=0; i<pr; i++)
    {
        cin >> in;
        if(su.count(in)!=0)
            st++;
    }
    cout << st;
    return 0;
}

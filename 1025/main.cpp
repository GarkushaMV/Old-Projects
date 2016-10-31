#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int l=1, k=(n/2 + 1);
    multiset<int> s;
    multiset<int>::iterator it;
    int c;
    cin >> c;
    s.insert(c);
    it=s.end();
    it--;
    for(int i=1; i<n; i++)
    {
        cin >> c;
        s.insert(c);
        l++;
        if(l>k)
        {
            it=s.end();
            it--;
            s.erase(it);
        }
    }
    c=0;
    for(it=s.begin(); it!=s.end(); it++)
        c+=(*it)/2+1;
    cout << c;
}

#include <iostream>
#include <map>

using namespace std;

int main()
{
    char c;
    map<char, int> m;
    while(cin>>c)
        m[c]++;
    map<char, int>::iterator it=m.begin();
    c=(*it).first;
    for(it++; it!=m.end(); it++)
        if(m[c]<(*it).second)
            c=(*it).first;
    cout << c;
    return 0;
}

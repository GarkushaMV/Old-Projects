#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    float h;
    int w, n;
    cin >> h >> w >> n;
    int k=0, c=1;
    string s;
    while(n>0)
    {
        n--;
        cin >> s;
        if(k==0)
        {
            k=k+s.length();
        }
        else
        {
            k=k+s.length()+1;
        }
        if(k>w)
        {
            k=s.length();
            c++;
        }
    }
    h=c/h;
    cout << ceil(h) ;
}

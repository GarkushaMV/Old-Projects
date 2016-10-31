#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string s;
    ifstream in;
    in.open("input.txt");
    in >> s;
    in.close();
    int n=s.size(); //размер строки
    int a[n+1], b[n+1]; //верх и низ
    b[0]=0;
    a[0]=1;
    for(int i=1; i<=n; i++)
    {
        switch(s[(n-i)])
        {
        case 'R':
            {
                b[i]=min((b[i-1]+1), (a[i-1]+1));
                a[i]=min((b[i-1]+2), a[i-1]);
                break;
            }
        case 'L':
            {
                b[i]=min(b[i-1], (a[i-1]+2));
                a[i]=min((b[i-1]+1), (a[i-1]+1));
                break;
            }
        case 'B':
            {
                b[i]=min((b[i-1]+1), (a[i-1]+2));
                a[i]=min((b[i-1]+2), (a[i-1]+1));
                break;
            }
        }
    }
    ofstream out;
    out.open("output.txt");
    out << a[n];
    out.close();
}

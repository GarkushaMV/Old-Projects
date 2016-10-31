#include <iostream>

using namespace std;

int main()
{
    int qxx, zzz, in;
    cin >> qxx >> zzz;
    for(int i=0; i<10; i++)
    {
        cin >> in;
        zzz-=in*20;
    }
    if(qxx<=zzz)
        cout << "No chance.";
    else
        cout << "Dirty debug :(";
    return 0;
}

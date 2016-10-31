#include <iostream>

using namespace std;

int main()
{
    int lw, hg, up, dw;
    cin >> lw >> up >> hg >> dw;
    if(lw<hg)
        while(1)
    {
        lw+=up;
        if(hg<lw)
            break;
        else
        {
            hg-=dw;
            if(hg<lw)
            {
                hg=lw;
                break;
            }
        }
    }
    else
        hg=lw;
    cout << hg;
    return 0;
}

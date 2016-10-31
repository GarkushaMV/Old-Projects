#include <iostream>

using namespace std;


bool inboard(char a, char b)
{
    bool c;
    c=(a>=0)*(a<8)*(b>=0)*(b<8);
    return c;
}

void fre(signed char &pos, bool *a)
{
    char vert=pos/8, hor=pos%8;
    if(inboard(vert-1, hor-2) && a[(pos-10)])
        pos-=10;
    else
    {
        if(inboard(vert-1, hor+2) && a[(pos-6)])
             pos-=6;
        else
        {
            if(inboard(vert-2, hor-1) && a[(pos-17)])
                pos-=17;
            else
            {
                if(inboard(vert-2, hor+1) && a[(pos-15)])
                    pos-=15;
                else
                {
                    if(inboard(vert+2, hor-1) && a[(pos+15)])
                        pos+=15;
                    else
                    {
                        if(inboard(vert+2, hor+1) && a[(pos+17)])
                            pos+=17;
                        else
                        {
                            if(inboard(vert+1, hor-2) && a[(pos+6)])
                                pos+=6;
                            else
                                pos+=10;
                        }
                    }

                }
            }
        }
    }
}


int main()
{
    signed char c, pos;
    cin >> c;
    pos=(c-'A')*8;
    cin >> c;
    pos+=(c-'1');
    bool a[64];
    for(int i=0; i<64; i++)
        a[i]=1;
    for(int i=0; i<64; i++)
    {
        a[pos]=0;
        fre(pos, a);
        cout << char(pos/8+'A')<< int(pos%8+1) << "\n";
    }
    return 0;
}

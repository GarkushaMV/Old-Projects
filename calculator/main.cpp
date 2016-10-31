#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int a, b;
    cin >> setbase(8) >> a;
    char c;
    cin >> c;
    cin >> setbase(8) >> b;
    double r;
    r=a;
    switch(c)
    {
        case '*' :
        {
            r*=b;
            break;
        }
        case '/' :
        {
            r/=b;
            break;
        }
        case '-' :
        {
            r-=b;
            break;
        }
        case '+' :
        {
            r+=b;
            break;
        }
    }
    cout.setf (ios::oct, ios::basefield);
    cout << r;
    }

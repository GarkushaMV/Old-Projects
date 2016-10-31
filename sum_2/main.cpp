#include <iostream>
#include <string>
#include <float.h>

using namespace std;

int main()
{
    string s;
    cin >> s;
    if ( s == "long" )
        cout << LDBL_MANT_DIG - 1;
    else if ( s == "float")
        cout << FLT_MANT_DIG  - 1;
    else
        cout << DBL_MANT_DIG  - 1;
}

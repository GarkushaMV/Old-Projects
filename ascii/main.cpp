#include <iostream>
#include <locale.h>

using namespace std;

int main()
{
    setlocale ( LC_ALL, "Russian" );
    for( int i = 0; i <= 256; i++ )
        cout << i << ' ' << char(i) << '\n';
    return 0;
}

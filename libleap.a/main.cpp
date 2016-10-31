#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

int main()
{
    FILE *fp=fopen("libleap.a", "rb");
    int rc=0;
    while(rc!=EOF)
    {
        rc = getc(fp);
        cout << char(rc);
    }
    return 0;
}

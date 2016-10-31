#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    long double x, y;
    fstream in;
    fstream out;
    in.open("input.txt");
    out.open("output.txt");
    in >> x >> y;
    if(((x<=2)&& (x>=-3))&& ((y>=-4)&& (y<=6)))
        out << "YES";
    else
        out << "NO";
    return 0;
}

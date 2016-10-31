#include <iostream>

using namespace std;

int main()
{
    int a[1024];
    for(int i = 0; i<1024; i++)
        a[i] = i;
    char* b = (char*) a;
    int* c = (int*) (b + 3*sizeof(int));
    cout << *(c + 5);
    return 0;
}

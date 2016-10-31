#include <iostream>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;
    if(N*(K+1)>60)
        cout << "NO";
    else
        cout << "YES";
    return 0;
}

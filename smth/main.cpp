#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
    int n;
    cout << "insert size";
    cin >> n;
    n*=2;
    int g;
    cout << "which variant? (1 or 2)";
    cin >> g;
    bool b=(g==2);
    vector <int> a;
    cout << "and now enter your numbers";
    for(int i=0; i<n; i++)
    {
        cin >> g;
        if(((g>0)+b) && ((!(g%2))+b))
            a.push_back(g);
    }
    cout << "right numbers \n";
    for(vector<int>::iterator i=a.begin(); i!=a.end(); i++)
        cout << (*i) << "\n";
}

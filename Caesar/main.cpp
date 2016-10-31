#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<char> ab(33), as(33);


    string s;
    int k, b, j;
    cin >> s >> k;
    for (size_t i = 0; i < s.size(); ++i) {
        if ((s[i] >= 97) &&(s[i] <= 122)) {
            b = s[i] - 97;
            b += k;
            b %= 26;
            b += 97;
            s[i] = b;
        } else if ((s[i] >= 65) &&(s[i] <= 90)) {
            b = s[i] - 65;
            b += k;
            b %= 26;
            b += 65;
            s[i] = b;
        } else if ((s[i] >= -128) &&(s[i] <= -97)) {
            b = s[i] - (-128);
            b += k;
            b %= 32;
            b += -128;
            s[i] = b;
        }
    }
    cout << s;
}


//A 65
//Z 90
//a 97
//z 122

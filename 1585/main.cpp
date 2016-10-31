#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int a[3];
    a[0]=0;
    a[1]=0;
    a[2]=0;
    string s;
    while(n>0)
    {
        n--;
        cin >> s;
        if(s=="Emperor")
            a[0]++;
        else
        {
            if(s=="Macaroni")
                a[1]++;
            else
                a[2]++;
        }
        cin >> s;
    }
    //cout << a[0] << "\n" << a[1] << "\n" << a[2];
    if(a[0]>a[1])
    {
        if(a[0]>a[2])
            cout << "Emperor Penguin";
        else
            cout << "Little Penguin";
    }
    else
    {
        if(a[1]>a[2])
            cout << "Macaroni Penguin";
        else
            cout << "Little Penguin";
    }
    return 0;
}

#include "string"
#include "conio.h"
#include "locale.h"
#include "math.h"
#include "iostream"

using namespace std;

int main()
{
    int s;
    setlocale(LC_ALL, "rus");
    cout << "�������� ��� ��������� ��������: \n1 - ��� int; 2 - ��� string" << endl;
    cin >> s;
    switch(s)
    {
    case 1:

        int a[10], x, k;
        cout << "������� ���-�� ��������� ���� int: " << endl;
        cin >> x;
        cout << "������� ��������: " << endl;
        for (int i=0; i<x; i++)
        cin >> a[i];
        cout << endl;
        k=powf(2,x);
        for (int i=0; i<k; i++)
            {
                cout << "$\\{";
                for (int j=0; j<x; j++)
                    if (i & (1<<j))
                     cout << a[j] << ", ";
                     cout << "\\}$" << endl;
            }
    break;

    case 2:

        string b[10];
        int y, z;
        cout << "������� ���-�� ��������� ���� string: " << endl;
        cin >> y;
        /*cout << "������� ��������: " << endl;
        for (int i=0; i<y; i++)
        {
        cin >> b[i];
        }
        */
        for (int i=0; i<y; i++)
        {
            char c = i + '0';
            b[i] = "q_";
            b[i] += c;
        }
        cout << endl;
        z=powf(2,y);
        for (int i=0; i<z; i++)
            {
                cout << "$\\{";
                for (int j=0; j<y; j++)
                    if (i & (1<<j))
                    {
                        cout << b[j] << ", ";
                    }

                        cout << "\b\b\\}$ \\\\" << endl;
            }
    break;
    }

}

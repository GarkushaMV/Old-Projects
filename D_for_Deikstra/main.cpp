#include <iostream>
#include <set>

using namespace std;

int main()
{
    int n, m, i;
    cin >> n >> m;
    int** a=new int *[n];

    for(i=0; i<n; i++)
    {
        a[i]= new int [n];
        for(int j=0; j<n; j++)
            a[i][j]=-1;
    }
    int x, y, s;
    for(i=0; i<m; i++)
    {
        cin >> x >> y >> s;
        a[x][y]=s;
        a[y][x]=s;
    }
    cin >> s;
    a[s][s]=0;
    set<int> q;
    for(i=1; i<n; i++)
        if(a[s][i]!=-1)
            q.insert(i);
    while(q.empty()==0)
    {
        x=*(q.begin());
        q.erase((q.begin()));
        y=a[s][x];
        for(i=0; i<n; i++)
            if((a[x][i]!=-1) && ((a[s][i]>(a[x][i]+y)) or (a[s][i]==-1)))
            {
                a[s][i]=a[x][i]+y;
                a[i][s]=a[s][i];
                q.insert(i);
            }
    }
    for(i=0; i<n; i++)
        cout << a[s][i] << ' ';
    return 0;
}

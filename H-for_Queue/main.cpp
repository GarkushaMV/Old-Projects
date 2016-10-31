#include <iostream>
#include <set>
#include <queue>

using namespace std;
#define K 3

int main()
{
    priority_queue<signed long long> que[(K+1)];
    priority_queue<signed long long> task[K];
    queue<long long> time;
    int i;
    int n;
    long long k[K];
    int t[K];
    for(i=0; i<K; i++)
        cin >> k[K];
    for(i=0; i<K; i++)
        cin >> t[K];
    cin >> n;
    long long s, z;
    z=0;
    for(i=0; i<n; i++)
    {
        cin >> s;
        que[0].push((-s));
        s-=z;
        if(s!=0)
        {
            time.push(s);
            z+=s;
        }
    }
    z=0;
    bool b;
    int cnt[K];
    for(i=0; i<K; i++)
        cnt[i]=0;
    while(time.empty()==0)
    {
        s=time.front();
        z+=s;
        cout << s << ' ' << z << endl;
        time.pop();
        for(i=0; i<K; i++)
        {
           cout << 5 << endl;
            b=task[i].empty();
            if(!b)
                b=b&&task[i].top()<=z;
            while(!b)
            {
                n=task[i].top();
                cout << "   " <<  n << endl;
                que[(i+1)].push(n);
                cnt[i]--;
                task[i].pop();
                b=!(task[i].empty());
                if(b)
                    b=b&&task[i].top()<=z;
                cout << ' ' << i << endl;
            }
        }
        for(i=0; i<K; i++)
        {
            b=que[i].empty();
            if(!b)
                b=b&&que[i].top()<=z;
            while(!b && cnt[i]<=k[i])
            {
                n=que[i].top()+t[i];
                task[i].push(n);
                cnt[i]++;
                n-=z;
                if(n!=0)
                    time.push(n);
                que[i].pop();
                b=(que[i].empty());
                if(!b)
                    b=b&&que[i].top()<=z;
                cout << ' ' << (-i) << endl;
            }
        }
    }
    /*set<long long>::iterator q=que[K].end();
    cout << que[K].size();
    q--;
    n=(*q);
    for(i=0; i<K; i++)
        n-=t[i];
    cout << (*q);*/
}

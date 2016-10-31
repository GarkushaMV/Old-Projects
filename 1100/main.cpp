#include <iostream>
#include <vector>
#include <map>

int main ()
{
    int n;
    std::cin >> n;
    std::map<int, std::vector<int> > count;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;
        count [b].push_back (a);
    }
    std::map<int, std::vector<int> >::reverse_iterator it = count.rbegin ();
    while (it != count.rend ())
    {
        int _cnt = it->second.size ();
        for (int i = 0; i < _cnt; i++)
            std::cout << it->second [i] << " " << it->first << std::endl;
        it++;
    }
    return 0;
}

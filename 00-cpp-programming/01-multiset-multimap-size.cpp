#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::multiset;

int main(void)
{

    multiset<int> s;
    s.insert(1);
    s.insert(1);
    s.insert(0);
    s.insert(2);

    cout << "The set size is: " << s.size() << endl;

    return 0;
}

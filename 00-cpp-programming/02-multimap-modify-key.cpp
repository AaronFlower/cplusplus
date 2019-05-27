#include <iostream>
#include <string>
#include <map>

using std::map;
using std::cout;
using std::endl;
using std::string;


int main(void) {

    map<int, string> m;

    m.insert({100, "Apple"});
    m.insert({101, "Banana"});
    m.insert({102, "Cat"});

    /**
     * 从 m 返回的 pair 可以看出我们的 first 是不可以修改的。在编译时，通过对 const 的检查就可以知道其错误。
     */
    std::pair<const int, string> &x = *m.begin();
    /* std::pair<int, string> &x = *m.begin(); */
    /* x.first = 103; */

    x.second = "APPLE";

    for (auto e : m) {
        cout << e.second << endl;
    }

    return 0;
}

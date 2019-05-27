#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;


vector<const char *> foo() {
    string s1 = "Hello";
    string s2 = "World";
    // 对 c_str() 返回的是 const char *, 在函数执行后会被释放。
    vector<const char *> res;

    /* res.push_back("Hee"); */
    res.push_back(s1.c_str());
    res.push_back(s1.c_str());
    return res;
}

int main(void)
{

    vector<const char*> res = foo();
    // 输出结果是未知道的。因为 foo() 函数在执行结束后，会为 s1, s2 调用析构函数，会释放 stack 的。
    for (auto str : res) {
        cout << str[0] << endl;
    }

    return 0;
}

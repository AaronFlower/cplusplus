#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <fstream>
#include <string>

using std::fstream;
using std::string;

/**
 * 对结构体可以直接读写，但不里面不要有成员函数。
 */
struct node {
    char key;
    float value;
};

class Solution {
public:
    void writeComplexData(string name, node *data, size_t len) {
        fstream ofile(name, std::ios::out | std::ios::binary);

        ofile.write((char *)data, sizeof(node) * len);

        ofile.close();
    }

    void readComplexData(string name, node *data, size_t len) {
        fstream ifile(name, std::ios::in | std::ios::binary);

        ifile.read((char *)data, sizeof(node) * len);

        ifile.close();
    }
};

#endif /* ifndef MY_SOLUTION__ */

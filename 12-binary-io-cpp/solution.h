#ifndef MY_SOLUTION__
#define MY_SOLUTION__

#include <fstream>
#include <string>

using std::fstream;
using std::string;

class node {
public:
    char key;
    float value;
    node() = default;
    node(char k, float v):key(k), value(v) {}
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

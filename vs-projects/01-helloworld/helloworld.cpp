#include <iostream>
#include <vector>
#include <string>

using std::string, std::vector;
using std::cout, std::endl;

int main() {
    vector<string> msg{"Hello", "C++", "World", "from", "VS Code!"};

    for (const string& word: msg) {
        cout << word << " ";
    }
    cout << endl;
    return 0;

}
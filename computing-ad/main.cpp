#include <iostream>
#include <string>
#include <set>
#include "src/InvIndex.h"

using std::string;
using std::cout;
using std::endl;

typedef string Word;


int main() {
    InvIndex<Word> index;

    vector<vector<Word>> docs = {
            {"hello", "world", "kid"} , // Doc 0
            {"catcher", "in", "the", "rye"}, // Doc 1
            {"the", "old", "man", "and", "the", "sea"} // Doc 2
    };

    for (auto doc:docs) {
        index.add(doc);
    }

    vector<Word> query{"hello"};
    set<DocId> docIds;

    index.retrieve(query,docIds);

    cout << "The 'hello' in the doc: "  << endl;
    for (auto id:docIds) {
        cout << id << "\t";
    }
    cout << endl;

    query = {"the"};
    index.retrieve(query,docIds);
    cout << "The 'the' in the doc: "  << endl;
    for (auto id:docIds) {
        cout << id << "\t";
    }
    cout << endl;

    query = {"the", "man"};
    index.retrieve(query,docIds);
    cout << "The 'the man' in the doc: "  << endl;
    for (auto id:docIds) {
        cout << id << "\t";
    }
    cout << endl;

    return 0;
}
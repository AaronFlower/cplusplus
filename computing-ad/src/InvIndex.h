//
// Created by eason on 2020/1/9.
//

#ifndef C___INVINDEX_H
#define C___INVINDEX_H

#include <vector>
#include <map>
#include <set>

using std::vector;
using std::map;
using std::set;
using std::make_pair;

typedef int DocId;

// TKey 是文档中的关键词: word; 通过继承 map, 我们就不用去维护空间的。
template<class TKey>
class InvIndex : public map<TKey, vector<int>> {
public:
    vector<vector<TKey>> docs;  // 文档正排表

public:
    /**
     * 向索引中添加一个文档.
     * - doc 文档
     * @param doc
     */
    void add(vector<TKey> &doc) {
        docs.push_back(doc);

        int curDocId = docs.size() - 1;

        for (auto keyWord:doc) {
            auto it = this->find(keyWord);
            if (it == this->end()) {
                this->insert(make_pair(keyWord, vector<int>{curDocId}));
            } else {
                it->second.push_back(curDocId);
            }
        }
    }

    void retrieve(vector<TKey> &query, set<DocId > &docIds) {
        docIds.clear();

        for (auto queryKey: query) {
            auto it = this->find(queryKey);
            if (it != this->end()) {
                docIds.insert(it->second.begin(), it->second.end());
            }
        }
    }
};

#endif //C___INVINDEX_H

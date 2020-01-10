//
// Created by eason on 2020/1/9.
//

#ifndef C___DNF_H
#define C___DNF_H

#include <vector>
#include <map>
#include <set>

using std::vector;
using std::map;
using std::set;
using std::pair;
using std::make_pair;

class Assignment {
public:
    int attribute;
    bool belong;
    int value;
};

typedef vector<Assignment> Conjunction;

typedef vector<Conjunction> DNF;

// Conjunction 倒排索引的数据结构
// 第一层的 key 是 length, 第二层的 key 是 Assignment 中的 <attribute, value>.
// 最终的 Value 是 <Conjunction, bool>, 把 Conjunction 换成 ID 不行吗？
// 第一版定义成了 ConjInner 会不会好点那？

typedef map<int, map<pair<int, int>, vector<pair<Conjunction, bool>>>> ConjIndex;

class ConjunctionInvIndex {
public:
    ConjIndex index;

    vector<pair<Conjunction, bool>> zeroConjList;

    /**
     * 添加一个 Conjunction
     * @param conj
     */
    void add(Conjunction& conj) {
        // 含有 ∈ 的 Assignment 数目, 所以用简单的 size() 函数可能不太行？
        int K = conj.size();

        if (K == 0) {
            zeroConjList.push_back(make_pair(conj, true));
        }

        for (auto assignment:conj) {
            auto key = make_pair(assignment.attribute, assignment.value);
            auto value = make_pair(conj, assignment.belong);
            index[K][key].push_back(value);
        }
    }

    /**
     * 给定多个 Assignments 的交，返回符合条件的 Conjunction 集合.
     * @param assigns
     * @param conjs
     */
    void retrieve(vector<Assignment> &assigns, set<Conjunction>& conjs) {
        ConjIndex::iterator it = index.begin();

        for (; it != index.end(); ++it) {
            vector<vector<pair<Conjunction, bool>>> lists;
            vector<int> positions, lists_size;

            // 根据 assignments 的条件数目对查询剪枝
            int K = it->first;
            if (K > assigns.size()) break; // 我们的 map 是有序的 map; 所以可以 break;

            // 初始化匹配该 assigns 的倒排链列表 lists 和各列表的当前游标 positions
            // 以及各列表长度 list_size
            initPostingLists(lists, positions, assigns, it->second);

            // 当 K == 0 时，后续按 K == 1 处理。
            if (K == 0) {
                lists.push_back(zeroConjList);
                positions.push_back(0);
                K = 1;
            }

            // lists 的 size 太小，以到于没有 Conjunction 能满足条件
            if (lists.size() < K) {
                continue;
            }

            while (positions[K - 1] < lists_size[K - 1]) {
                // 按照首个 conjID 的升序对 lists 进行排序， ∉ 的 Conjunction 在前
                SortByCurrentEntries(lists, positions, lists_size);
                if ((*lists)[positions[0]].first = (*lists)[positions[K - 1]].first) {
                    // 跳过包含 ∉ 操作的 Conjunction
                    if ((*lists)[positions[0]].second == false) {
                        for (int L = K; L < assigns.size(); ++L) {
                            if (positions[L] != positions[0]) {
                                break;
                            } else {
                                (*lists)[L].skipto(positions[0] + 1);
                            }
                        }
                    }

                } else {
                    // 找到满足条件的 Conjunction 并跳过它
                    conjs.insert((*lists)[positions[K - 1]].first)

                    for (int i = 0; i < K; ++i) {
                        (*lists)[i].skipto(positions[K - 1] + 1);
                    }
                }
            } else {
                // 跳过前 K-1 个 posting list
                for (int i = 0; i < K; ++i) {
                    (*lists)[i].skipto(positions[K - 1]);
                }
            }
        }
    }
};

// 这里继承的是倒排索引
class DNFInvIndex: public InvIndex<Conjunction> {
public:
    ConjunctionInvIndex conjIndex;

    void add(vector<Conjunction> &conjs) {
        for (auto conj:conjs) {
            auto it = conjIndex.find(conj);

            if (it == this.end()) {
                conjIndex.add(conj);
            }
        }

        // 调用父类的 add 方法
        InvIndex<Conjunction>::add(conjs);
    }

    // 查询 DNF 表达式，返回对应的广告 ID
    void retrieve(const vector<vector<Assignment>>& query, set<int>& dnfIDs) {
        set<Conjunction> conj_set;
        for (auto conj:query) {
            conjIndex.retrieve(conj, conj_set);
        }

        for (auto conj:conj_set) {
            InvIndex<Conjunction>::retrieve(conj, dnfIDs);
        }
    }
};


#endif //C___DNF_H

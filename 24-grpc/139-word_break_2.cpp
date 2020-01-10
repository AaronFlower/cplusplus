//
// Created by eason on 2019/11/23.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using std::string;
using std::vector;
using std::unordered_set;


class Solution {
public:
    /**
     * 用一个 dpSentences 来保存每个位置的组合而成的句子会有一个问题；那就是遇到 "aaaaa" 这种情况会呈指数增长；
     * 那就会 Time Limit Exceeded; 或者 Memory Limit Exceeded
     * word-break2 用 dp 方法就会超时了；所以还是用 dfs 来搜索吧；
     */
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> set(wordDict.begin(), wordDict.end());

        vector<bool> dp(s.size() + 1, false);
        vector<vector<string>> dpSentences(s.size() + 1, vector<string>{});

        dp[0] = true;
        dpSentences[0] = vector<string>{""};

        for (int i = 1; i <= s.size(); ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (dp[j]) {
                    string word = s.substr(j, i - j);
                    if (set.count(word)) {
                        dp[i] = true;
                        for (auto sentence:dpSentences[j]) {
                            dpSentences[i].push_back(sentence + " " + word);
                        }
                    }
                }
            }
        }

        for (auto d:dpSentences) {
            std::cout << "d size():" << d.size() << std::endl;
        }

        return dpSentences[s.size()];
    }
};

int main() {
    Solution s;
    vector<string> dicts{"apple", "pen"};
    auto res = s.wordBreak("applepenapple", dicts);
    for (auto w:res) {
        std::cout << w << std::endl;
    }
    string str = "aaaaaaa";
    vector<string> dict{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    res = s.wordBreak(str, dict);
    for (auto w:res) {
        std::cout << w << std::endl;
    }
    return 0;
}


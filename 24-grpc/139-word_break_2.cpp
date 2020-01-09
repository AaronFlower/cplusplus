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
    bool wordBreak(string s, vector<string> wordDict) {
        unordered_set<string> set(wordDict.begin(), wordDict.end());

        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (dp[j] && set.count(s.substr(j, i - j))) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};

int main() {
    Solution s;
    std::cout << s.wordBreak("applepenapple", {"apple", "pen"}) << std::endl;

    return 0;
}


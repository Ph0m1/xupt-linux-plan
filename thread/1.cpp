#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSatisfied(std::vector<int>& customers, std::vector<int>& grumpy, int minutes) {
        int n = customers.size();
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = std::max(dp[i - 1], dp[i - 1] + customers[i] - grumpy[i]);
        }
        return dp[n];
    }
};

#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Coin Change-1, Dynamic Programming, 20180829
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // sort(coins.begin(), coins.end());
        int length = coins.size();
        vector<vector<int>> dp(length, vector<int>(amount + 1, 0));
        for (int j = 0; j <= amount; j++)
            if (j % coins[0] == 0) dp[0][j] = j / coins[0];
            else dp[0][j] = -1;
        for (int i = 1; i < length; i++) {
            for (int j = 0; j <= amount; j++) {
                if (coins[i] > j)
                    dp[i][j] = dp[i - 1][j];
                else {
                    int temp = INT_MAX;
                    for (int k = 0; k <= j / coins[i]; k++) {
                        int remaining = j - coins[i] * k;
                        if (dp[i - 1][remaining] != -1)
                            temp = min(temp, dp[i - 1][remaining] + k);
                    }
                    dp[i][j] = temp == INT_MAX ? -1 : temp;
                }
            }
        }
        return dp[length - 1][amount];
    }
};

int main(int argc, char **argv) {
    vector<int> coins{1, 2, 5};
    int amount = 11;

    int result;
    Solution *solution = new Solution;
    result = solution->coinChange(coins, amount);
    cout << "coins: ";
    for (int c : coins)
        cout << c << ", ";
    cout << endl;
    cout << "amount: " << amount << endl;
    cout << "fewest number of coins: " << result << endl;

    coins.clear();
    coins.push_back(2);
    amount = 3;

    result = solution->coinChange(coins, amount);
    cout << "coins: ";
    for (int c : coins)
        cout << c << ", ";
    cout << endl;
    cout << "amount: " << amount << endl;
    cout << "fewest number of coins: " << result << endl;

    coins.clear();
    coins.push_back(186);
    coins.push_back(419);
    coins.push_back(83);
    coins.push_back(408);
    amount = 6249;

    result = solution->coinChange(coins, amount);
    cout << "coins: ";
    for (int c : coins)
        cout << c << ", ";
    cout << endl;
    cout << "amount: " << amount << endl;
    cout << "fewest number of coins: " << result << endl;
}

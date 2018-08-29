#include <vector>
#include <limits.h>
#include <iostream>
#include <algorithm>
using namespace std;

// Coin Change-2, Depth-first Search, 20180821
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        int minCnt = INT_MAX;
        if (_coinChange(coins, amount, 
                        coins.size() - 1, 0, minCnt))
            return minCnt;
        return -1;
    }
    
private:
    bool _coinChange(vector<int> &coins, int rest, 
                     int index, int cnt, int &minCnt) {
        if (rest == 0) {
            if (cnt < minCnt) minCnt = cnt;
            return true;
        }
        if (rest < 0 || index < 0) return false;
        if (cnt >= minCnt) return false; // pruning
        bool result = false;
        for (int i = rest / coins[index]; i >= 0; i--)
            if (_coinChange(coins, rest - i * coins[index], 
                        index - 1, cnt + i, minCnt))
                result = true;
        return result;
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

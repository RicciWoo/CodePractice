#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Cutting Metal Surplus/Metals, Brute Force, 20181111
class Solution {
public:
    int maxProfit(int cutCost, int unitPrice, vector<int> &lengths) {
        if (lengths.empty()) {
            return 0;
        }

        int maxLength = 0;
        for (int i = 0; i < lengths.size(); i++) {
            maxLength = max(maxLength, lengths[i]);
        }

        int maxProfit = 0;
        for (int i = 1; i <= maxLength; i++) {
            int profit = 0;
            for (int j = 0; j < lengths.size(); j++) {
                int metals = lengths[j] / i;
                int cuts = metals;
                if (cuts > 0 && lengths[j] % i == 0) {
                    cuts--;
                }
                profit += metals * i * unitPrice - cuts * cutCost;
                maxProfit = max(maxProfit, profit);
            }
        }

        return maxProfit;
    }
};

int main(int argc, char **argv) {
    int cutCost = 1;
    int unitPrice = 10;
    vector<int> lengths{26, 103, 59};

    int result;
    Solution *solution = new Solution;
    result = solution->maxProfit(cutCost, unitPrice, lengths);
    cout << "cut cost = " << cutCost << endl;
    cout << "unit price = " << unitPrice << endl;
    cout << "lengths = [";
    for (int l : lengths) {
        cout << l << ", ";
    }
    cout << "]" << endl;

    cout << "max profit = " << result << endl;
}
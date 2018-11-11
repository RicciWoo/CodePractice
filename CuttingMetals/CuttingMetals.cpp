#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// Cutting Metals, Binary Search, 20181111
class Solution {
public:
    int maxProfit(int cutCost, int unitPrice, vector<int> &lengths) {
        if (lengths.empty()) {
            return 0;
        }

        int start = 1, end = 0;
        for (int i = 0; i < lengths.size(); i++) {
            end = max(end, lengths[i]);
        }
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (_profit(cutCost, unitPrice, mid, lengths) >= 0) {
                start = mid;
            } else {
                end = mid;
            }
        }

        int maxCut = 0;
        if (_profit(cutCost, unitPrice, end, length) >= 0) {
            maxCut = end;
        } else if (_profit(cutCost, unitPrice, start, length) >= 0) {
            maxCut = start;
        }

        return maxCut;
    }

private:
    int _profit(int cutCost, int unitPrice, int length, 
                vector<int> &lengths) {
        int profit = 0;
        for (int i = 0; i < lengths.size(); i++) {
            int metals = lengths[i] / length;
            int cut = metals;
            if (metals > 0 && lengths[i] % length == 0) {
                metals--;
            }
            profit += metals * length * unitPrice - cut * cutCost;
        }
    }
};

int main(int argc, char **argv) {
    int cutCost = 1;
    int unitPrice = 10
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
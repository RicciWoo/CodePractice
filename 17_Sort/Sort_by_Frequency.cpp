#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Sort by Frequency, use Sort
class myComp {
public:
    bool operator() (const pair<int, int> &a, 
                     const pair<int, int> &b) {
        return a.second > b.second;
    }
};

class Solution {
public:
    vector<int> frequencySort(vector<int> &array) {
        unordered_map<int, char> cm;
        for (int i = 0; i < array.size(); i++) {
            cm.insert({array[i], 0});
            cm[array[i]]++;
        }
        vector<pair<int, int>> vec(cm.begin(), cm.end());
        sort(vec.begin(), vec.end(), myComp());
        vector<int> result;
        for (int i = 0; i < vec.size(); i++)
            for (int j = 0; j < vec[i].second; j++)
                result.push_back(vec[i].first);
        return result;
    }
};

int main(int argc, char **argv) {
    vector<int> array{1, 4, 5, 5, 7, 8, 1, 3, 4, 5, 8, 11, 
                    2, 5, 6, 6, 7, 10, 2, 3, 5, 8, 10, 13};
    cout << "Input: [";
    for (int a : array) cout << a << ", ";
    cout << "]" << endl;

    vector<int> result;
    Solution *solution = new Solution;
    result = solution->frequencySort(array);

    cout << "Output: [";
    for (int r : result) cout << r << ", ";
    cout << "]" << endl;
}

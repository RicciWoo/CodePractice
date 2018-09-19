#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

// Sort by Frequency, use Sort
// if elements with the same frequency, sort by appearance
class myComp {
public:
    bool operator() (const pair<int, pair<int, int>> &a, 
                     const pair<int, pair<int, int>> &b) {
        if (a.second.first != b.second.first) 
            return a.second.first > b.second.first;
        return a.second.second < b.second.second;
    }
};

class Solution {
public:
    vector<int> frequencySort(vector<int> &array) {
        unordered_map<int, pair<int, int>> hm;
        for (int i = 0; i < array.size(); i++) {
            if (!hm.count(array[i]))
                hm.insert({array[i], {0, i}});
            hm[array[i]].first++;
        }
        vector<pair<int, pair<int, int>>> vec(hm.begin(), 
                                              hm.end());
        sort(vec.begin(), vec.end(), myComp());
        vector<int> result;
        for (int i = 0; i < vec.size(); i++)
            for (int j = 0; j < vec[i].second.first; j++)
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

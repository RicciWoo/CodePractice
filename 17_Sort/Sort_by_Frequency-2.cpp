#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

// Sort by Frequency, use Sort
class myComp {
public:
    bool operator() (const pair<int, int> &a, 
                     const pair<int, int> &b) {
        if (a.second != b.second) 
            return a.second > b.second;
        return a.first < b.first;
    }
};

class Solution {
public:
    vector<int> frequencySort(vector<int> &array) {
        unordered_map<int, int> hm;
        for (int i = 0; i < array.size(); i++) {
            if (!hm.count(array[i]))
                hm.insert({array[i], 0});
            hm[array[i]]++;
        }
        vector<pair<int, int>> vec;
        for (int i = 0; i < array.size(); i++)
            vec.push_back({i, hm[array[i]]});
        sort(vec.begin(), vec.end(), myComp);
        vector<int> result;
        for (int i = 0; i < array.size(); i++)
            result.push_back(array[vec[i].first]);
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

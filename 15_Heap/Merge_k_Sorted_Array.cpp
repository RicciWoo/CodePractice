#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Merge k Sorted Array, use Heap
class myComp {
public:
    bool operator() (const pair<int, int> &a, 
                     const pair<int, int> &b) {
        return a.first > b.first;
    }
};

class Solution {
public:
    vector<int> mergeKArray(vector<vector<int>> &arrays) {
        int k = arrays.size(), n = arrays[0].size();
        priority_queue<pair<int, int>, 
                       vector<pair<int, int>>, myComp> pq;
        for (int i = 0; i < arrays.size(); i++)
            pq.push({arrays[i][0], i * n});
        vector<int> result;
        while (!pq.empty()) {
            pair<int, int> item = pq.top();
            pq.pop();
            int val = item.first;
            int i = item.second / n, j = item.second % n;
            if (++j < n) pq.push({arrays[i][j], i * n + j});
            result.push_back(val);
        }
        return result;
    }
};

int main(int argc, char **argv) {
    vector<vector<int>> arrays{{1, 4, 5, 5, 7, 8}, 
                               {1, 3, 4, 5, 8, 11}, 
                               {2, 5, 6, 6, 7, 10}, 
                               {2, 3, 5, 8, 10, 13}};
    cout << "Input:" << endl;
    cout << "[" << endl;
    for (vector<int> array: arrays) {
        cout << "   [";
        for (int a : array) cout << a << ", ";
        cout << "]" << endl;
    }
    cout << "]" << endl;

    vector<int> result;
    Solution *solution = new Solution;
    result = solution->mergeKArray(arrays);

    cout << "Output: [";
    for (int r : result) cout << r << ", ";
    cout << "]" << endl;
}

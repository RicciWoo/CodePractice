#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Group Anagrams-2, use Hash Map
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> hm;
        vector<vector<string>> results;
        for (string str : strs) {
            string sorted(str);
            sort(begin(sorted), end(sorted));
            if (!hm.count(sorted)) {
                vector<string> temp;
                hm[sorted] = temp;
            }
            hm[sorted].push_back(str);
        }
        for (auto &entry : hm) {
            vector<string> values = entry.second;
            sort(values.begin(), values.end());
            results.push_back(values);
        }
        return results;
    }
};

int main(int argc, char **argv) {
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> results;
    Solution *solution = new Solution;
    results = solution->groupAnagrams(strs);
    cout << "strings: ";
    for (string &str : strs) cout << "\"" << str << "\", ";
    cout << endl;
    cout << "grouped anagrams: " << endl;
    cout << "[ " << endl;
    for (vector<string> &result : results) {
        cout << "   [";
        for (string &str : result) cout << "\"" << str << "\", ";
        cout << "], " << endl;
    }
    cout << "]" << endl;
}

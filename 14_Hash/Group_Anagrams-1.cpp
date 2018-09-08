#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Group Anagrams-1, use Hash Map
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> hm;
        vector<vector<string>> results;
        for (string str : strs) {
            string sorted(str);
            sort(begin(sorted), end(sorted));
            if (hm.count(sorted))
                hm[sorted].push_back(str);
            else {
                vector<string> temp;
                temp.push_back(str);
                hm[sorted] = temp;
            }
        }
        for (auto it = hm.begin(); it != hm.end(); it++) {
        // for (unordered_map<string, vector<string>>::iterator it = 
        //      hm.begin(); it != hm.end(); it++) {
            vector<string> values = it->second;
            sort(values.begin(), values.end());
            results.push_back(values);
        }
        // for (auto &entry : hm) {
        // //for (const pair<string, vector<string>> &entry : hm) {
        //     vector<string> values = entry.second;
        //     sort(values.begin(), values.end());
        //     results.push_back(values);
        // }
        // return results;
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

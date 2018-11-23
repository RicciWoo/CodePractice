#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Royal Names, Hash Map and Sort, 20181123
// LeetCode 13 - Roman to Integer, Hash Map
class myComp {
public:
    operator() (const pair<string, int> &a, 
                const pair<string, int> &b ) {
        if (a.first == b.first) {
            return a.second >= b.second;
        }
        return a.first < b.first;
    }
    
};

class Solution {
public:
    vector<string> getSortedList(vector<string> &names) {
        if (names.empty()) {
            return names;
        }

        vector<pair<string, int>> nums;
        for (int i = 0; i < names.size(); i++) {
            string str = names[i];
            int pos = str.find(' ');
            string name = str.substr(0, pos);
            string sub = str.substr(pos + 1);
            int num = _romanToInt(sub);
            nums.push_back(make_pair(name, num));
        }

        vector<string> results;
        sort(nums.begin(), nums.end(), myComp());
        for (int i = 0; i < nums.size(); i++) {
            string result = nums[i].first;
            result += _intToRoman(nums[i].second);
            results.push_back(result);
        }

        return results;
    }

private:
    int _romanToInt(string &s) {
        if (s.empty()) {
            return 0;
        }
        
        unordered_map<char, int> nums;
        nums['I'] = 1;
        nums['V'] = 5;
        nums['X'] = 10;
        nums['L'] = 50;
        nums['C'] = 100;
        nums['D'] = 500;
        nums['M'] = 1000;
        
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            if (i > 0 && nums[s[i]] > nums[s[i - 1]])
                result += nums[s[i]] - 2 * nums[s[i - 1]];
            else
                result += nums[s[i]];
        }
        return result;
    }

    string _intToRoman(int num) {
        if (num > 3999) {
            return "";
        }
        
        // M = 1000, D = 500, C = 100, L = 50, X = 10, V = 5
        vector<int> radix{1000, 900, 500, 400, 100, 90, 
                          50, 40, 10, 9, 5, 4, 1};
        vector<string> symbol{"M", "CM", "D", "CD", "C", "XC", 
                              "L", "XL", "X", "IX", "V", "IV", "I"};
        
        string roman;
        for (int i = 0; num > 0; i++) {
            int count = num / radix[i];
            num %= radix[i];
            while (count--) {
                roman += symbol[i];
            }
        }
        
        return roman;
    }
};

int main(int argc, char **argv) {
    vector<string> names{"Louis IX", "Louis VIII"};
    vector<string> results;
    Solution *solution = new Solution;
    results = solution->getSortedList(names);
    cout << "Royal names:" << endl;
    for (string &n : names) {
        cout << "  \"" << n << "\"" << endl;
    }
    cout << "sorted names:" << endl;
    for (string &r : results) {
        cout << "  \"" << r << "\"" << endl;
    }

    names = vector<string>{"Philippe I", "Philip II"};
    results = solution->getSortedList(names);
    cout << "Royal names:" << endl;
    for (string &n : names) {
        cout << "  \"" << n << "\"" << endl;
    }
    cout << "sorted names:" << endl;
    for (string &r : results) {
        cout << "  \"" << r << "\"" << endl;
    }
}
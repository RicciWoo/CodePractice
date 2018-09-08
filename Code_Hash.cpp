/******************** Hash ********************/

// Word Pattern, use Hash Map
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char, string> hm;
        unordered_map<string, char> hm_r;
        vector<string> words = _split(str);
        if (pattern.size() != words.size()) return false;
        for (int i = 0; i < pattern.size(); i++) {
            char a = pattern[i];
            string b = words[i];
            if (!hm.count(a)) hm[a] = b;
            else if (hm[a] != b) return false;
            if (!hm_r.count(b)) hm_r[b] = a;
            else if (hm_r[b] != a) return false;
        }
        return true;
    }
    
private:
    vector<string> _split(string s) {
        istringstream iss(s);
        vector<string> words(istream_iterator<string>{iss}, 
                            istream_iterator<string>());
        return words;
    }
};

// Word Pattern II, use Hash Map
class Solution {
public:
    bool wordPatternMatch(string pattern, string str) {
        unordered_map<char, string> hm;
        unordered_set<string> hs;
        return _isMatch(str, 0, pattern, 0, hm, hs);
    }
    
private:
    bool _isMatch(string str, int i, string pattern, int j, 
                  unordered_map<char, string> &hm, 
                  unordered_set<string> &hs) {
        if (i == str.size() && j == pattern.size()) 
            return true;
        if (i == str.size() || j == pattern.size())
            return false;
        char c = pattern[j];
        if (hm.count(c)) {
            string s = hm[c];
            if (str.compare(i, s.size(), s)) return false;
            else return _isMatch(str, i + s.size(), 
                                 pattern, j + 1, hm, hs);
        }
        for (int k = i; k < str.size(); k++) {
            string p = str.substr(i, k - i + 1);
            if (hs.count(p)) continue;
            hm[c] = p;
            hs.insert(p);
            if (_isMatch(str, k + 1, pattern, j + 1, hm, hs))
                return true;
            hm.erase(c);
            hs.erase(p);
        }
        return false;
    }
};

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
        // for (unordered_map<string, vector<string>>::iterator it = 
        //      hm.begin(); it != hm.end(); it++) {
        //     vector<string> values = it->second;
        //     sort(values.begin(), values.end());
        //     results.push_back(values);
        // }
        for (const pair<string, vector<string>> &entry : hm) {
            vector<string> values = entry.second;
            sort(values.begin(), values.end());
            results.push_back(values);
        }
        return results;
    }
};

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














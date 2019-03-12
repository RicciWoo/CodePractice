/******************** Preview ********************/

// Longest Palindrome, LeetCode 409
class Solution {
public:
    int longestPalindrome(string s) {
        if (s.empty()) return 0;
        
        unordered_set<char> charSet;
        for (int i = 0; i < s.size(); i++) {
            if (charSet.count(s[i])) 
                charSet.erase(s[i]);
            else charSet.insert(s[i]);
        }
        
        int oddAppr = charSet.size();
        if (oddAppr > 0) oddAppr -= 1;
        return s.size() - oddAppr;
    }
};

// Implement strStr(), LeetCode 28
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        if (haystack.empty()) return -1;
        
        int n = haystack.size() - needle.size() + 1;
        for (int i = 0; i < n; i++) {
            int j = 0;
            for (j = 0; j < needle.size(); j++) {
                if (haystack[i + j] != needle[j])
                    break;
            }
            if (j == needle.size()) return i;
        }
        
        return -1;
    }
};

// Implement strStr(), Rabin Karp Algorithm, LeetCode 28
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        if (haystack.empty()) return -1;
        
        const int BASE = 1000000;
        int m = needle.size();
        
        // 31 ^ m
        int power = 1;
        for (int i = 0; i < m; i++)
            power = (power * 31) % BASE;
        
        int needleCode = 0;
        for (int i = 0; i < m; i++)
            needleCode = (needleCode * 31 + needle[i]) % BASE;
        
        int hashCode = 0;
        for (int i = 0; i < haystack.size(); i++) {
            // abc + d
            hashCode = (hashCode * 31 + haystack[i]) % BASE;
            if (i < m - 1) continue;
            
            // abcd - a
            if (i >= m) {
                hashCode -= (haystack[i - m] * power) % BASE;
                if (hashCode < 0) hashCode += BASE;
            }
            
            // double check the string
            if (hashCode == needleCode) {
                if (haystack.substr(i - m + 1, m) == needle)
                    return i - m + 1;
            }
        }
        
        return -1;
    }
};

// Valid Palindrome, Two Pointers, LeetCode 125
class Solution {
public:
    /**
     * @param s: A string
     * @return: Whether the string is a valid palindrome
     */
    bool isPalindrome(string &s) {
        if (s.empty()) {
            return true;
        }
        
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (left < s.size() && !isalnum(s[left])) {
                left++;
            }
            
            while (right >= 0 && !isalnum(s[right])) {
                right--;
            }
            
            if (tolower(s[left]) != tolower(s[right])) {
                break;
            } else {
                left++;
                right--;
            }
        }
        
        return left >= right;
    }
};

// Longest Palindromic Substring, Center Enumeration, LeetCode 5
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        
        int start = 0, len = 0, longest = 0;
        for (int i = 0; i < s.size(); i++) {
            len = _longestPalindrome(s, i, i);
            if (len > longest) {
                longest = len;
                start = i - len / 2;
            }
            
            len = _longestPalindrome(s, i, i + 1);
            if (len > longest) {
                longest = len;
                start = i - len / 2 + 1;
            }
        }
        
        return s.substr(start, longest);
    }
    
private:
    int _longestPalindrome(string &s, int left, int right) {
        int len = 0;
        while (left >= 0 && right < s.size()) {
            if (s[left] != s[right]) break;
            len += (left == right ? 1 : 2);
            left--;
            right++;
        }
        
        return len;
    }
};

// Longest Palindromic Substring, Center Enumeration, LeetCode 5
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        
        int n = s.size();
        vector<vector<bool>> opt(n, vector<bool>(n, false));
        
        int longest = 1, start = 0;
        for (int i = 0; i < n; i++)
            opt[i][i] = true;
        // use upper triangle
        for (int i = 0; i < n - 1; i++) {
            opt[i][i + 1] = s[i] == s[i + 1];
            if (opt[i][i + 1]) {
                start = i;
                longest = 2;
            }
        }
        
        // must start from bottom to top
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                opt[i][j] = opt[i + 1][j - 1] && s[i] == s[j];
                
                if (opt[i][j] && j - i + 1 > longest) {
                    start = i;
                    longest = j - i + 1;
                }
            }
        }
         
        return s.substr(start, longest);
    }
};

// Longest Palindrome Subsequence, Dynamic Programming, LeetCode 516
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) return 0;
        if (s.size() == 1) return 1;
        
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
        
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        
        return dp[0][n - 1];
    }
};

// Valid Palindrome II, Two Pointers, LeetCode 680
class Solution {
public:
    /**
     * @param s: a string
     * @return: nothing
     */
    bool validPalindrome(string &s) {
        if (s.size() <= 2) return true;
        
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                break;
            }
            left++;
            right--;
        }
        
        if (left >= right) {
            return true;
        }
        
        return _isSubPalindrome(s, left + 1, right) || 
               _isSubPalindrome(s, left, right - 1);
    }
    
private:
    bool _isSubPalindrome(string &s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        
        return true;
    }
};

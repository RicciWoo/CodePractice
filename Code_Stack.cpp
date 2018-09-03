/******************** Stack ********************/

// Valid Parentheses, use stack
class Solution {
public:
    bool isValid(string s) {
        stack<char> pair;
        if (s.size() == 0) return true;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') 
                pair.push(s[i]);
            else if (s[i] == ')') {
                if (pair.empty()) return false;
                if (pair.top() != '(') return false;
                else pair.pop();
            }
            else if (s[i] == ']') {
                if (pair.empty()) return false;
                if (pair.top() != '[') return false;
                else pair.pop();
            }
            else if (s[i] == '}') {
                if (pair.empty()) return false;
                if (pair.top() != '{') return false;
                else pair.pop();
            }
        }
        return pair.empty();
    }
};

// Max Stack with peekMax and popMax
class MaxStack {
public:
    /** initialize your data structure here. */
    stack<int> element;
    stack<int> maxVal;
    
    void push(int x) {
        int curMax;
        if (element.empty()) curMax = INT_MIN;
        else curMax = maxVal.top();
        curMax = max(curMax, x);
        maxVal.push(curMax);
        element.push(x);
    }
    
    int pop() {
        maxVal.pop();
        int result = element.top();
        element.pop();
        return result;
    }
    
    int top() {
        return element.top();
    }
    
    int peekMax() {
        return maxVal.top();
    }
    
    int popMax() {
        stack<int> temp;
        int result = peekMax();
        while (top() != result) temp.push(pop());
        pop();
        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }
        return result;
    }
};

// Bad Hair Day, see Cows
class Solution {
public:
    int seeCows(vector<int> &cow) {
        int totalNum = 0;
        stack<int> cowStack;
        for (int i = 0; i < cow.size(); i++) {
            if (cowStack.empty() || cow[i] < cowStack.top())
                cowStack.push(cow[i]);
            else {
                while (!cowStack.empty() && cow[i] >= cowStack.top()) {
                    cowStack.pop();
                    totalNum += cowStack.size();
                }
                cowStack.push(cow[i]);
            }
        }
        while (!cowStack.empty()) {
            cowStack.pop();
            totalNum += cowStack.size();
        }
        return totalNum;
    }
};

// Remove Duplicate Letters-1
class Solution {
public:
    string removeDuplicateLetters(string s) {
        if (s.size() == 0) return s;
        vector<int> cnt(26, 0);
        for (int i = 0; i < s.size(); i++)
            cnt[s[i] - 'a']++;
        int pos = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] < s[pos]) pos = i;
            if (--cnt[s[i] - 'a'] == 0) break;
        }
        string sub = "";
        for (int i = pos + 1; i < s.size(); i++)
            if (s[i] != s[pos]) sub += s.substr(i, 1);
        return s[pos] + removeDuplicateLetters(sub);
    }
};

// Remove Duplicate Letters-2
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> freqs(26, 0);
        for (int i = 0; i < s.size(); i++)
            freqs[s[i] - 'a']++;
        vector<bool> visited(26, false);
        stack<char> charSt;
        for (int i = 0; i < s.size(); i++) {
            freqs[s[i] - 'a']--;
            if (visited[s[i] - 'a']) continue;
            while (!charSt.empty() && s[i] < charSt.top() && 
                   freqs[charSt.top() - 'a'] > 0) {
                visited[charSt.top() - 'a'] = false;
                charSt.pop();
            }
            charSt.push(s[i]);
            visited[s[i] - 'a'] = true;
        }
        string result = "";
        while (!charSt.empty()) {
            result += charSt.top();
            charSt.pop();
        }
        reverse(begin(result), end(result));
        return result;
    }
};



















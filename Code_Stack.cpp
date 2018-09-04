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

// Max Stack with peekMax() and popMax()
class MaxStack {
private:
    stack<int> eleSt;
    stack<int> maxSt;
    
public:
    void push(int x) {
        int curMax = INT_MIN;
        if (!maxSt.empty()) curMax = maxSt.top();
        curMax = max(curMax, x);
        eleSt.push(x);
        maxSt.push(curMax);
    }
    
    int pop() {
        int result = eleSt.top();
        eleSt.pop();
        maxSt.pop();
        return result;
    }
    
    int top() {
        return eleSt.top();
    }
    
    int peekMax() {
        return maxSt.top();
    }
    
    int popMax() {
        stack<int> temSt;
        int result = peekMax();
        while (top() != result) temSt.push(pop());
        pop();
        while (!temSt.empty()) {
            push(temSt.top());
            temSt.pop();
        }
        return result;
    }
};

// Min Stack with getMin()
class MinStack {
private:
    stack<int> eleSt;
    stack<int> minSt;
    
public:
    void push(int x) {
        int curMin = INT_MAX;
        if (!minSt.empty()) curMin = minSt.top();
        curMin = min(curMin, x);
        eleSt.push(x);
        minSt.push(curMin);
    }
    
    void pop() {
        eleSt.pop();
        minSt.pop();
    }
    
    int top() {
        return eleSt.top();
    }
    
    int getMin() {
        return minSt.top();
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

// Remove Duplicate Letters-1, use recursion
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

// Remove Duplicate Letters-2, use stack
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> cnt(26, 0);
        for (int i = 0; i < s.size(); i++)
            cnt[s[i] - 'a']++;
        stack<char> chStack;
        vector<bool> visited(26, false);
        for (int i = 0; i < s.size(); i++) {
            cnt[s[i] - 'a']--;
            if (visited[s[i] - 'a']) continue;
            while (!chStack.empty() && s[i] < chStack.top() && 
                   cnt[chStack.top() - 'a'] > 0) {
                visited[chStack.top() - 'a'] = false;
                chStack.pop();
            }
            chStack.push(s[i]);
            visited[s[i] - 'a'] = true;
        }
        string result = "";
        while (!chStack.empty()) {
            result += chStack.top();
            chStack.pop();
        }
        reverse(begin(result), end(result));
        return result;
    }
};

// Largest Rectangle in Histogram, use stack
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int area = 0;
        stack<int> hStack;
        for (int i = 0; i < heights.size(); i++) {
            if (hStack.empty() || heights[i] > heights[hStack.top()])
                hStack.push(i);
            else {
                int start = hStack.top();
                hStack.pop();
                int width = hStack.empty() ? i : i - hStack.top() - 1;
                area = max(area, heights[start] * width);
                i--;
            }
        }
        while (!hStack.empty()) {
            int start = hStack.top();
            hStack.pop();
            int width = hStack.empty() ? heights.size() : 
                        heights.size() - hStack.top() - 1;
            area = max(area, heights[start] * width);
        }
        return area;
    }
};

// Implement Stack using Queues
class MyStack {
public:
    /** Initialize your data structure here. */
    queue<int> q1, q2;
    
    /** Push element x onto stack. */
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int result = q1.front();
        q1.pop();
        return result;
    }
    
    /** Get the top element. */
    int top() {
        return q1.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q1.empty();
    }
};

// Implement Queue using Stacks
class MyQueue {
public:
    /** Initialize your data structure here. */
    stack<int> s1, s2;
    
    /** Push element x to the back of queue. */
    void push(int x) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(x);
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int result = s1.top();
        s1.pop();
        return result;
    }
    
    /** Get the front element. */
    int peek() {
        return s1.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return s1.empty();
    }
};

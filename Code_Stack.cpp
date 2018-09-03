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





















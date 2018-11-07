/******************** Stack, Queue, Hash, Heap ********************/

// Moving Average from Data Stream
// Sliding Window Average from Data Stream
class MovingAverage {
public:
    /*
     * @param size: An integer
     */
    MovingAverage(int size) {
        this->sum = 0;
        this->size = size;
    }

    /*
     * @param val: An integer
     * @return:  
     */
    double next(int val) {
        sum += val;
        if (q.size() == size) {
            sum -= q.front();
            q.pop();
        }
        q.push(val);
        return sum / q.size();
    }
    
private:
    queue<int> q;
    double sum;
    int size;
};

// Sliding Window Median

// Sliding Window Maximum

// Sliding Window Matrix Maximum

// Sliding Window Unique Element Sum

// LRU Cache
class CacheNode {
public:
    int key, val;
    CacheNode *next;
    CacheNode(int key, int val) {
        this->key = key;
        this->val = val;
        this->next = nullptr;
    }
};
class LRUCache {
public:
    /*
    * @param capacity: An integer
    */LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->dummy = new CacheNode(0, 0);
        this->tail = this->dummy;
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        if (!keyToPrev.count(key)) {
            return -1;
        }
        _moveToTail(key);
        return tail->val;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        if (get(key) != -1) {
            CacheNode *prev = keyToPrev[key];
            prev->next->val = value;
            return;
        }
        
        if (size < capacity) {
            size++;
            CacheNode *curr = new CacheNode(key, value);
            tail->next = curr;
            keyToPrev[key] = tail;
            tail = curr;
            return;
        }
        
        // replace the first node with new key, value
        CacheNode *head = dummy->next;
        keyToPrev.erase(head->key);
        head->key = key;
        head->val = value;
        keyToPrev[key] = dummy;
        _moveToTail(key);
    }
    
private:
    int capacity, size;
    CacheNode *dummy, *tail;
    unordered_map<int, CacheNode *> keyToPrev;

    void _moveToTail(int key) {
        CacheNode *prev = keyToPrev[key];
        CacheNode *curr = prev->next;
        
        if (tail == curr) {
            return;
        }
        
        prev->next = prev->next->next;
        tail->next = curr;
        keyToPrev[prev->next->key] = prev;
        keyToPrev[curr->key] = tail;
        tail = curr;
    }
};

// Insert Delete GetRandom O(1)
class RandomizedSet {
private:
    vector<int> nums;
    unordered_map<int, int> num2index;

public:
    RandomizedSet() {
        srand(time(nullptr));
    }

    /*
     * @param val: a value to the set
     * @return: true if the set did not already contain the specified element or false
     */
    bool insert(int val) {
        if (num2index.count(val)) {
            return false;
        }
        
        num2index.insert({val, nums.size()});
        nums.push_back(val);
        return true;
    }

    /*
     * @param val: a value from the set
     * @return: true if the set contained the specified element or false
     */
    bool remove(int val) {
        if (!num2index.count(val)) {
            return false;
        }
        
        int index = num2index[val];
        if (index < nums.size() - 1) {
            int last = nums[nums.size() - 1];
            nums[index] = last;
            num2index[last] = index;
        }
        num2index.erase(val);
        nums.pop_back();
        return true;
    }

    /*
     * @return: Get a random element from the set
     */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

// Load Balancer

// Insert Delete GetRandom O(1) Duplicates Allowed

// First Unique Character in a String
class ListCharNode {
public:
    char val;
    ListCharNode *next;
    ListCharNode(char val) {
        this->val = val;
        this->next = nullptr;
    }
};

class Solution {
private:
    unordered_map<char, ListCharNode *> charToPrev;
    unordered_set<char> dupChars;
    ListCharNode *dummy = new ListCharNode('.');
    ListCharNode *tail = dummy;

public:
    /**
     * @param str: str: the given string
     * @return: char: the first unique character in a given string
     */
    char firstUniqChar(string &str) {
        for (int i = 0; i < str.size(); i++) {
            _add(str[i]);
        }
        return _firstUniqueChar();
    }
    
    void _add(char c) {
        if (dupChars.count(c)) {
            return;
        }
        
        if (!charToPrev.count(c)) {
            ListCharNode *node = new ListCharNode(c);
            charToPrev.insert({c, tail});
            tail->next = node;
            tail = tail->next;
            return;
        }
        
        // delete the existing node
        ListCharNode *prev = charToPrev[c];
        prev->next = prev->next->next;
        if (prev->next == nullptr) {
            // tail node removed
            tail = prev;
        } else {
            // force update the value
            charToPrev[prev->next->val] = prev;
        }
        
        charToPrev.erase(c);
        dupChars.insert(c);
    }
    
    char _firstUniqueChar() {
        return dummy->next->val;
    }
};

// First Unique Number in a Stream II
class DataStream {
public:
    DataStream(){
        // dummy node
        head = new ListNode(-1);
        tail = head;
    }
    
    /**
     * @param number: next number in stream
     * @return: nothing
     */
    void add(int number) {
        if (duplicates.count(number)) {
            return;
        }
        
        if (numToPrev.count(number)) {
            _remove(number);
            duplicates.insert(number);
        } else {
            ListNode *node = new ListNode(number);
            numToPrev[number] = tail;
            tail->next = node;
            tail = tail->next;
        }
    }

    /**
     * @return: the first unique number in stream
     */
    int firstUnique() {
        if (head->next != nullptr) {
            return head->next->val;
        }
        return -1;
    }
    
private:
    ListNode *head, *tail;
    unordered_map<int, ListNode *> numToPrev;
    unordered_set<int> duplicates;
    
    void _remove(int number) {
        ListNode *prev = numToPrev[number];
        prev->next = prev->next->next;
        numToPrev.erase(number);
        
        // change tail and prev of next
        if (prev->next != nullptr) {
            numToPrev[prev->next->val] = prev;
        } else {
            tail = prev;
        }
    }
};

// Subarray Sum

// Copy List with Random Pointer

// Anagrams

// Longest Consecutive Sequence

// Ugly Number II
class myComp {
public:
    bool operator() (long long &a, long long &b) {
        return a >= b;
    }
};

class Solution {
public:
    /**
     * @param n: An integer
     * @return: the nth prime number as description.
     */
    int nthUglyNumber(int n) {
        priority_queue<long long, 
                       vector<long long>, myComp> heap;
        unordered_set<long long> inHeap;
        vector<long long> primes{2, 3, 5};
        for (int i = 0; i < 3; i++) {
            heap.push(primes[i]);
            inHeap.insert(primes[i]);
        }
        long long number = 1;
        for (int i = 1; i < n; i++) {
            number = heap.top();
            heap.pop();
            for (int j = 0; j < 3; j++) {
                long long newNum = number * primes[j];
                if (!inHeap.count(newNum)) {
                    heap.push(newNum);
                    inHeap.insert(newNum);
                }
            }
        }
        return (int)number;
    }
};

// Merge K Sorted Lists

// K Closest Points
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
Point globalOrigin;
class myComp {
public:
    bool operator() (const Point &a, const Point &b) {
        long long aDist = _getDist(a, globalOrigin);
        long long bDist = _getDist(b, globalOrigin);
        if (aDist != bDist) {
            return aDist < bDist;
        }
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.y < b.y;
    }
    
private:
    long long _getDist(const Point &a, const Point &b) {
        return pow((long long)(a.x - b.x), 2) + 
               pow((long long)(a.y - b.y), 2);
    }
};
class Solution {
public:
    /**
     * @param points: a list of points
     * @param origin: a point
     * @param k: An integer
     * @return: the k closest points
     */
    vector<Point> kClosest(vector<Point> &points, 
                           Point &origin, int k) {
        globalOrigin = Point(origin.x, origin.y);
        priority_queue<Point, vector<Point>, myComp> heap;
        
        int n = points.size();
        for (int i = 0; i < n; i++) {
            Point p = points[i];
            heap.push(p);
            if (heap.size() > k) {
                heap.pop();
            }
        }
        
        vector<Point> results;
        while (!heap.empty()) {
            Point p = heap.top();
            heap.pop();
            results.push_back(p);
        }
        reverse(results.begin(), results.end());
        return results;
    }
};

// Top K Largest Number II
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a >= b;
    }
};
class Solution {
private:
    priority_queue<int, vector<int>, myComp> heap;
    int k;
    
public:
    /*
    * @param k: An integer
    */Solution(int k) {
        this->k = k;
    }

    /*
     * @param num: Number to be added
     * @return: nothing
     */
    void add(int num) {
        heap.push(num);
        if (heap.size() > k) {
            heap.pop();
        }
    }

    /*
     * @return: Top k element
     */
    vector<int> topk() {
        vector<int> results;
        while (!heap.empty()) {
            results.push_back(heap.top());
            heap.pop();
        }
        
        for (int i = 0; i < results.size(); i++) {
            heap.push(results[i]);
        }
        
        reverse(results.begin(), results.end());
        return results;
    }
};

// High Five

// Merge K Sorted Arrays
/**
 * Definition of ListNode
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *         this->val = val;
 *         this->next = NULL;
 *     }
 * }
 */
class myComp {
public:
    bool operator() (ListNode *a, ListNode *b) {
        return a->val >= b->val;
    }
};
class Solution {
public:
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) {
            return nullptr;
        }
        
        priority_queue<ListNode *, 
                       vector<ListNode *>, myComp> heap;
        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                heap.push(lists[i]);
            }
        }
        
        ListNode dummy(-1);
        ListNode *head = &dummy;
        while (!heap.empty()) {
            ListNode *node = heap.top();
            heap.pop();
            head->next = node;
            head = head->next;
            if (head->next != nullptr) {
                heap.push(head->next);
            }
        }
        return dummy.next;
    }
};

// Data Stream Median

// Top K Largest Numbers
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a >= b;
    }
};
class Solution {
public:
    /**
     * @param nums: an integer array
     * @param k: An integer
     * @return: the top k largest numbers in array
     */
    vector<int> topk(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, myComp> heap;
        for (int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
            if (heap.size() > k) {
                heap.pop();
            }
        }
        
        vector<int> results;
        while (!heap.empty()) {
            results.push_back(heap.top());
            heap.pop();
        }
        
        reverse(results.begin(), results.end());
        return results;
    }
};

// Top K Frequent Elements

// Kth Smallest Number in Sorted Matrix

// Implement Stack by Two Queues
class Stack {
private:
    queue<int> q1;
    queue<int> q2;
    
    void _moveItems() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
    }
    
public:
    /*
     * @param x: An integer
     * @return: nothing
     */
    void push(int x) {
        q1.push(x);
    }

    /*
     * @return: nothing
     */
    void pop() {
        _moveItems();
        q1.pop();
        swap(q1, q2);
    }

    /*
     * @return: An integer
     */
    int top() {
        _moveItems();
        int item = q1.front();
        q1.pop();
        q2.push(item);
        swap(q1, q2);
        return item;
    }

    /*
     * @return: True if the stack is empty
     */
    bool isEmpty() {
        return q1.empty();
    }
};

// Implement Queue by Two Stacks
class MyQueue {
private:
    stack<int> s1;
    stack<int> s2;
    
    void _stack2ToStack1() {
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }
    
public:
    /*
     * @param element: An integer
     * @return: nothing
     */
    void push(int element) {
        s2.push(element);
    }

    /*
     * @return: An integer
     */
    int pop() {
        if (s1.empty()) {
            _stack2ToStack1();
        }
        int item = s1.top();
        s1.pop();
        return item;
    }

    /*
     * @return: An integer
     */
    int top() {
        if (s1.empty()) {
            _stack2ToStack1();
        }
        return s1.top();
    }
};

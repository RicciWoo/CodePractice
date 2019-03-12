/******************** Stack, Queue, Hash, Heap ********************/

// LeetCode 346 - Moving Average from Data Stream, 
// Sliding Window Average from Data Stream, Queue, 20190129
class MovingAverage {
private:
    queue<int> q;
    int sum;
    int size;
    
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        this->sum = 0;
        this->size = size;
    }
    
    double next(int val) {
        sum += val;
        if (q.size() == size) {
            sum -= q.front();
            q.pop();
        }
        q.push(val);
        return (double)sum / q.size();
    }
};

// LeetCode 480 - Sliding Window Median, Tree Set, 20190129
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int> &nums, 
                                       int k) {
        vector<double> results;
        if (nums.empty() || k <= 0) {
            return results;
        }
        if (k == 1) {
            results.insert(results.begin(), 
                           nums.begin(), nums.end());
            return results;
        }
        
        bool isEven = k % 2 == 0;
        
        multiset<int> max, min;
        for (int i = 0; i < k; i++) {
            max.insert(nums[i]);
        }
        for (int i = 0; i < k / 2; i++) {
            min.insert(*max.rbegin());
            max.erase(prev(max.end()));
        }
        _saveMedian(max, min, isEven, results);
        
        for (int i = k; i < nums.size(); i++) {
            if (max.count(nums[i - k])) {
                max.erase(max.find(nums[i - k]));
                max.insert(nums[i]);
            } else {
                min.erase(min.find(nums[i - k]));
                min.insert(nums[i]);
            }
            
            if (*max.rbegin() > *min.begin()) {
                int temp = *max.rbegin();
                max.erase(prev(max.end()));
                max.insert(*min.begin());
                min.erase(min.begin());
                min.insert(temp);
            }
            
            _saveMedian(max, min, isEven, results);
        }
        
        return results;
    }
    
private:
    void _saveMedian(multiset<int> &max, 
                     multiset<int> &min, bool isEven, 
                     vector<double> &results) {
        double median = *max.rbegin();
        if (isEven) {
            median += *min.begin();
            median /= 2.;
        }
        results.push_back(median);
    }
};

// LintCode 360 - Sliding Window Median, Tree Set, 20190129
class Solution {
public:
    vector<int> medianSlidingWindow(vector<int> &nums, int k) {
        vector<int> results;
        if (nums.empty() || k <= 0) {
            return results;
        }
        if (k == 1) {
            return nums;
        }
        
        multiset<int> max, min;
        for (int i = 0; i < k; i++) {
            max.insert(nums[i]);
        }
        for (int i = 0; i < k / 2; i++) {
            min.insert(*max.rbegin());
            max.erase(prev(max.end()));
        }
        results.push_back(*max.rbegin());
        
        for (int i = k; i < nums.size(); i++) {
            if (max.count(nums[i - k])) {
                max.erase(max.find(nums[i - k]));
                max.insert(nums[i]);
            } else {
                min.erase(min.find(nums[i - k]));
                min.insert(nums[i]);
            }
            
            if (*max.rbegin() > *min.begin()) {
                int temp = *max.rbegin();
                max.erase(prev(max.end()));
                max.insert(*min.begin());
                min.erase(min.begin());
                min.insert(temp);
            }
            
            results.push_back(*max.rbegin());
        }
        
        return results;
    }
};

// LeetCode 239 - Sliding Window Maximum, Deque, 20190202
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        vector<int> results;
        if (nums.empty()) {
            return results;
        }
        
        deque<int> q;
        for (int i = 0; i < nums.size(); i++) {
            if (!q.empty() && q.front() == i - k) {
                q.pop_front();
            }
            
            while (!q.empty() && nums[q.back()] < nums[i]) {
                q.pop_back();
            }
            
            q.push_back(i);
            
            if (i >= k - 1) {
                results.push_back(nums[q.front()]);
            }
        }
        
        return results;
    }
};

// LintCode 692 - Sliding Window Unique Element Sum, 
// Hash Table, 20190202
class Solution {
public:
    int slidingWindowUniqueElementsSum(vector<int> &nums, int k) {
        if (nums.empty() || k <= 0) {
            return 0;
        }
        
        int count = 0, sum = 0;
        unordered_map<int, int> hashmap;
        for (int i = 0; i < nums.size(); i++) {
            if (!hashmap.count(nums[i])) {
                hashmap[nums[i]] = 1;
                count++;
            } else {
                hashmap[nums[i]]++;
                if (hashmap[nums[i]] == 2) {
                    count--;
                }
            }
            
            if (i >= k - 1) {
                sum += count;
                
                hashmap[nums[i - k + 1]]--;
                if (hashmap[nums[i - k + 1]] == 1) {
                    count++;
                } else if (hashmap[nums[i - k + 1]] == 0) {
                    hashmap.erase(nums[i - k + 1]);
                    count--;
                }
            }
        }
        
        if (nums.size() < k) {
            return count;
        }
        return sum;
    }
};

// LeetCode 146 - LRU Cache, Hash Table, 20190129
class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        this->dummy = new CacheNode(-1, -1);
        this->tail = this->dummy;
    }
    
    int get(int key) {
        if (!keyToPrev.count(key)) {
            return -1;
        }
        
        _moveToTail(key);
        return tail->val;
    }
    
    void put(int key, int value) {
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
        
        // replace the first node with (key, value)
        CacheNode *head = dummy->next;
        keyToPrev.erase(head->key);
        head->key = key;
        head->val = value;
        keyToPrev[key] = dummy;
        _moveToTail(key);
    }
    
private:
    struct CacheNode {
        int key, val;
        CacheNode *next;
        CacheNode(int key, int val) {
            this->key = key;
            this->val = val;
            this->next = nullptr;
        }
    };
    
    int capacity, size;
    CacheNode *dummy, *tail;
    unordered_map<int, CacheNode *> keyToPrev;
    
    void _moveToTail(int key) {
        CacheNode *prev = keyToPrev[key];
        CacheNode *curr = prev->next;
        if (curr == tail) {
            return;
        }
        
        prev->next = curr->next;
        tail->next = curr;
        keyToPrev[prev->next->key] = prev;
        keyToPrev[curr->key] = tail;
        tail = curr;
    }
};

// LeetCode 380 - Insert Delete GetRandom O(1), Hash Table, 20190129
class RandomizedSet {
private:
    vector<int> nums;
    unordered_map<int, int> num2Index;

public:
    RandomizedSet() {
        srand(time(nullptr));
    }
    
    bool insert(int val) {
        if (num2Index.count(val)) {
            return false;
        }
        
        num2Index[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (!num2Index.count(val)) {
            return false;
        }
        
        int index = num2Index[val];
        if (index != nums.size() - 1) {
            int last = nums[nums.size() - 1];
            nums[index] = last;
            num2Index[last] = index;
        }
        nums.pop_back();
        num2Index.erase(val);
        return true;
    }
    
    int getRandom() {
        if (nums.empty()) {
            return -1;
        }
        return nums[rand() % nums.size()];
    }
};

// LintCode 526 - Load Balancer, Hash Table, 20190202
class LoadBalancer {
private:
    vector<int> servers;
    unordered_map<int, int> serIndex;

public:
    LoadBalancer() {
        srand(time(nullptr));
    }

    void add(int server_id) {
        if (serIndex.count(server_id)) {
            return;
        }
        
        serIndex[server_id] = servers.size();
        servers.push_back(server_id);
    }

    void remove(int server_id) {
        if (!serIndex.count(server_id)) {
            return;
        }
        
        int index = serIndex[server_id];
        if (index != servers.size() - 1) {
            int last = servers[servers.size() - 1];
            servers[index] = last;
            serIndex[last] = index;
        }
        servers.pop_back();
        serIndex.erase(server_id);
    }

    int pick() {
        return servers[rand() % servers.size()];
    }
};

// LeetCode 381 - Insert Delete GetRandom O(1) - 
// Duplicates Allowed, Hash Table, 20190203
class RandomizedCollection {
private:
    vector<pair<int, int>> nums;
    unordered_map<int, vector<int>> num2Index;
    
public:
    RandomizedCollection() {
        srand(time(nullptr));
    }
    
    bool insert(int val) {
        if (!num2Index.count(val)) {
            num2Index[val] = vector<int>();
        }
        num2Index[val].push_back(nums.size());
        int index = num2Index[val].size() - 1;
        nums.push_back({val, index});
        return index == 0;
    }
    
    bool remove(int val) {
        if (!num2Index.count(val)) {
            return false;
        }
        
        vector<int> &indices = num2Index[val];
        int index = indices[indices.size() - 1];
        if (index != nums.size() - 1) {
            pair<int, int> last = nums[nums.size() - 1];
            nums[index] = last;
            num2Index[last.first][last.second] = index;
        }
        nums.pop_back();
        indices.pop_back();
        if (indices.empty()) {
            num2Index.erase(val);
        }
            
        return true;
    }
    
    int getRandom() {
        if (nums.empty()) {
            return -1;
        }
        return nums[rand() % nums.size()].first;
    }
};

// LeetCode 387 - First Unique Character in a String, 
// Hash Table, 20190203
class Solution {
private:
    struct IndexListNode {
        int index;
        IndexListNode *next;
        IndexListNode(int index) {
            this->index = index;
            this->next = nullptr;
        }
    };
    
    unordered_map<char, IndexListNode *> charToPrev;
    unordered_set<char> dupChars;
    IndexListNode *dummy = new IndexListNode(-1);
    IndexListNode *tail = dummy;
    
public:
    int firstUniqChar(string s) {
        if (s.empty()) {
            return -1;
        }
        
        for (int i = 0; i < s.size(); i++) {
            _addToList(s, i);
        }
        
        return _firstUniqueChar();
    }
    
private:
    void _addToList(string &s, int i) {
        if (dupChars.count(s[i])) {
            return;
        }
        
        if (!charToPrev.count(s[i])) {
            charToPrev[s[i]] = tail;
            tail->next = new IndexListNode(i);
            tail = tail->next;
            return;
        }
        
        // delete existing node
        IndexListNode *prev = charToPrev[s[i]];
        prev->next = prev->next->next;
        if (prev->next == nullptr) {
            tail = prev;
        } else {
            charToPrev[s[prev->next->index]] = prev;
        }
        charToPrev.erase(s[i]);
        dupChars.insert(s[i]);
    }
    
    int _firstUniqueChar() {
        if (dummy->next == nullptr) {
            return -1;
        }
        return dummy->next->index;
    }
};

// LintCode 209 - First Unique Character in a String, 
// Hash Table, 20190203
class Solution {
private:
    struct CharListNode {
        char val;
        CharListNode *next;
        CharListNode(char val) {
            this->val = val;
            this->next = nullptr;
        }
    };
    
    unordered_map<char, CharListNode *> charToPrev;
    unordered_set<char> dupChars;
    CharListNode *dummy = new CharListNode('.');
    CharListNode *tail = dummy;
    
public:
    char firstUniqChar(string &str) {
        if (str.empty()) {
            return '.';
        }
        
        for (int i = 0; i < str.size(); i++) {
            _addToList(str[i]);
        }
        
        return _firstUniqueChar();
    }
    
private:
    void _addToList(char c) {
        if (dupChars.count(c)) {
            return;
        }
        
        if (!charToPrev.count(c)) {
            charToPrev[c] = tail;
            tail->next = new CharListNode(c);
            tail = tail->next;
            return;
        }
        
        // delete existing node
        CharListNode *prev = charToPrev[c];
        prev->next = prev->next->next;
        if (prev->next == nullptr) {
            tail = prev;
        } else {
            charToPrev[prev->next->val] = prev;
        }
        charToPrev.erase(c);
        dupChars.insert(c);
    }
    
    char _firstUniqueChar() {
        return dummy->next->val;
    }
};

// LintCode 960 - First Unique Number in a Stream II, 
// Hash Table, 20190203
class DataStream {
private:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int val) {
            this->val = val;
            this->next = nullptr;
        }
    };
    
    unordered_map<int, ListNode *> numToPrev;
    unordered_set<int> dupNums;
    ListNode *dummy, *tail;

public:
    DataStream(){
        // dummy node
        dummy = new ListNode(-1);
        tail = dummy;
    }
    
    void add(int number) {
        if (dupNums.count(number)) {
            return;
        }
        
        if (!numToPrev.count(number)) {
            numToPrev[number] = tail;
            tail->next = new ListNode(number);
            tail = tail->next;
            return;
        }
        
        ListNode *prev = numToPrev[number];
        prev->next = prev->next->next;
        if (prev->next == nullptr) {
            tail = prev;
        } else {
            numToPrev[prev->next->val] = prev;
        }
        numToPrev.erase(number);
        dupNums.insert(number);
    }

    int firstUnique() {
        if (dummy->next == nullptr) {
            return -1;
        }
        return dummy->next->val;
    }
};

// LintCode 138 - Subarray Sum, Hash Table, 20190203
class Solution {
public:
    vector<int> subarraySum(vector<int> &nums) {
        vector<int> results;
        if (nums.empty()) {
            return results;
        }
        
        unordered_map<int, int> hashmap;
        hashmap[0] = -1;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            
            if (hashmap.count(sum)) {
                results.push_back(hashmap[sum] + 1);
                results.push_back(i);
                return results;
            }
            
            hashmap[sum] = i;
        }
        
        return results;
    }
};

// LintCode 105 - Copy List with Random Pointer, 
// Hash Table, 20190213
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        unordered_map<RandomListNode *, 
                            RandomListNode *> hashmap;
        RandomListNode *dummy = new RandomListNode(0);
        RandomListNode *copy = dummy;
        while (head != nullptr) {
            if (hashmap.count(head)) {
                copy->next = hashmap[head];
            } else {
                copy->next = new RandomListNode(head->label);
                hashmap[head] = copy->next;
            }
            
            if (head->random != nullptr) {
                if (hashmap.count(head->random)) {
                    copy->next->random = hashmap[head->random];
                } else {
                    copy->next->random = new RandomListNode(
                                        head->random->label);
                    hashmap[head->random] = copy->next->random;
                }
            }
            
            copy = copy->next;
            head = head->next;
        }
        
        return dummy->next;
    }
};

// LintCode 171 - Anagrams, Hash Table, 20190214
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        vector<string> results;
        if (strs.empty()) {
            return results;
        }
        
        unordered_map<string, vector<string>> hashmap;
        for (int i = 0; i < strs.size(); i++) {
            string str = strs[i];
            sort(str.begin(), str.end());
            hashmap[str].push_back(strs[i]);
        }
        
        for (auto &entry : hashmap) {
            if (entry.second.size() > 1) {
                for (string &item : entry.second) {
                    results.push_back(item);
                }
            }
        }
        
        return results;
    }
};

// LeetCode 128 - Longest Consecutive Sequence, Hash Table, 20190214
class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        
        unordered_set<int> hashset;
        for (int i = 0; i < nums.size(); i++) {
            hashset.insert(nums[i]);
        }
        
        int longest = 0;
        for (int i = 0; i < nums.size(); i++) {
            hashset.erase(nums[i]);
            
            int down = nums[i] - 1;
            while (hashset.count(down)) {
                hashset.erase(down);
                down--;
            }
            
            int up = nums[i] + 1;
            while (hashset.count(up)) {
                hashset.erase(up);
                up++;
            }
            
            longest = max(longest, up - down - 1);
        }
        
        return longest;
    }
};

// LeetCode 264 - Ugly Number II, Heap, 20190215
class Solution {
public:
    int nthUglyNumber(int n) {
        if (n <= 1) {
            return n;
        }
        
        priority_queue<long long, 
                       vector<long long>, myComp> heap;
        unordered_set<long long> inHeap;
        vector<long long> primes{2, 3, 5};
        for (int i = 0; i < 3; i++) {
            heap.push(primes[i]);
            inHeap.insert(primes[i]);
        }
        
        long long number = 0;
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
    
private:
    struct myComp {
        bool operator() (long long &a, long long &b) {
            return a > b;
        }
    };
};

// LeetCode 23 - Merge K Sorted Lists, Heap, 20190215
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
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
        
        ListNode *dummy = new ListNode(-1);
        ListNode *head = dummy;
        while (!heap.empty()) {
            ListNode *node = heap.top();
            heap.pop();
            head->next = node;
            head = head->next;
            if (head->next != nullptr) {
                heap.push(head->next);
            }
        }
        
        return dummy->next;
    }
    
private:
    struct myComp {
        bool operator() (ListNode *a, ListNode *b) {
            return a->val >= b->val;
        }
    };
};

// LintCode 612 - K Closest Points, Heap, 20190215
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
class Solution {
public:
    vector<Point> kClosest(vector<Point> &points, 
                           Point &origin, int k) {
        vector<Point> results;
        if (points.empty() || points.size() < k) {
            return results;
        }
        
        globalOrigin = Point(origin.x, origin.y);
        priority_queue<Point, vector<Point>, myComp> heap;
        
        for (int i = 0; i < points.size(); i++) {
            Point p = points[i];
            heap.push(p);
            if (heap.size() > k) {
                heap.pop();
            }
        }
        
        while (!heap.empty()) {
            Point p = heap.top();
            heap.pop();
            results.push_back(p);
        }
        reverse(results.begin(), results.end());
        return results;
    }
    
private:
    struct myComp {
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
};

// LeetCode 973 - K Closest Points to Origin, Heap, 20190215
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& 
                                 points, int K) {
        vector<vector<int>> results;
        if (points.empty() || points.size() < K) {
            return results;
        }
        
        priority_queue<vector<int>, 
                       vector<vector<int>>, myComp> heap;
        for (int i = 0; i < points.size(); i++) {
            heap.push(points[i]);
            if (heap.size() > K) {
                heap.pop();
            }
        }
        
        while (!heap.empty()) {
            results.push_back(heap.top());
            heap.pop();
        }
        
        return results;
    }
    
private:
    struct myComp {
        bool operator() (vector<int> &a, vector<int> &b) {
            return a[0] * a[0] + a[1] * a[1] < 
                   b[0] * b[0] + b[1] * b[1];
        }
    };
};

// LintCode 545 - Top K Largest Number II, Heap, 20190216
class Solution {
private:
    struct myComp {
        bool operator() (const int &a, const int &b) {
            return a > b;
        }
    };

    priority_queue<int, vector<int>, myComp> heap;
    int k;
    
public:
    Solution(int k) {
        this->k = k;
    }

    void add(int num) {
        heap.push(num);
        if (heap.size() > k) {
            heap.pop();
        }
    }

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

// LintCode 613 - High Five, Heap, 20190216
/**
 * Definition for a Record
 * class Record {
 * public:
 *   int id, score;
 *   Record(int id, int score) {
 *     this->id = id;
 *     this->score = score;
 *   }
 * };
 */
class Solution {
public:
    map<int, double> highFive(vector<Record> &results) {
        map<int, double> high5s;
        if (results.empty()) {
            return high5s;
        }
        
        unordered_map<int, priority_queue<int>> scores;
        for (Record &rec : results) {
            scores[rec.id].push(rec.score);
        }
        
        for (auto &entry : scores) {
            if (entry.second.size() < 5) {
                continue;
            }
            
            double sum = 0;
            for (int i = 0; i < 5; i++) {
                sum += entry.second.top();
                entry.second.pop();
            }
            sum /= 5.;
            high5s[entry.first] = sum;
        }
        
        return high5s;
    }
};

// LintCode 486 - Merge K Sorted Arrays, Heap, 20190216
class Solution {
public:
    vector<int> mergekSortedArrays(vector<vector<int>> &arrays) {
        vector<int> result;
        if (arrays.empty()) {
            return result;
        }
        
        priority_queue<Element *, vector<Element *>, myComp> heap;
        for (int i = 0; i < arrays.size(); i++) {
            if (arrays[i].empty()) {
                continue;
            }
            Element *elem = new Element(i, 0, arrays[i][0]);
            heap.push(elem);
        }
        
        while (!heap.empty()) {
            Element *elem = heap.top();
            heap.pop();
            result.push_back(elem->val);
            if (++elem->col < arrays[elem->row].size()) {
                elem->val = arrays[elem->row][elem->col];
                heap.push(elem);
            }
        }
        
        return result;
    }
    
private:
    struct Element {
        int row, col, val;
        Element(int row, int col, int val) {
            this->row = row;
            this->col = col;
            this->val = val;
        }
    };
    
    struct myComp {
        bool operator() (const Element *a, const Element *b) {
            return a->val > b->val;
        }
    };
};

// LeetCode 295 - Find Median from Data Stream, Heap, 20190216
class MedianFinder {
public:
    void addNum(int num) {
        minHeap.push(num);
        maxHeap.push(minHeap.top());
        minHeap.pop();
        if (maxHeap.size() - minHeap.size() > 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
    }
    
    double findMedian() {
        if (minHeap.size() == maxHeap.size()) {
            return (minHeap.top() + maxHeap.top()) / 2.0;
        }
        return maxHeap.top();
    }
    
private:
    struct myComp {
        bool operator() (const int &a, const int &b) {
            return a > b;
        }
    };

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, myComp> minHeap;
};

// LintCode 81 - Find Median from Data Stream, Heap, 20190216
class Solution {
public:
    vector<int> medianII(vector<int> &nums) {
        vector<int> results;
        if (nums.empty()) {
            return results;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            addNum(nums[i]);
            results.push_back(findMedian());
        }
        
        return results;
    }
    
private:
    void addNum(int num) {
        minHeap.push(num);
        maxHeap.push(minHeap.top());
        minHeap.pop();
        if (maxHeap.size() - minHeap.size() > 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
    }
    
    int findMedian() {
        return maxHeap.top();
    }
    
    struct myComp {
        bool operator() (const int &a, const int &b) {
            return a > b;
        }
    };
    
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, myComp> minHeap;
};

// LintCode 544 - Top K Largest Numbers, Heap, 20190216
class Solution {
public:
    vector<int> topk(vector<int> &nums, int k) {
        vector<int> results;
        if (nums.empty() || k <= 0) {
            return results;
        }
        
        priority_queue<int, vector<int>, myComp> heap;
        for (int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
            if (heap.size() > k) {
                heap.pop();
            }
        }
        
        while (!heap.empty()) {
            results.push_back(heap.top());
            heap.pop();
        }
        
        reverse(results.begin(), results.end());
        return results;
    }

private:
    struct myComp {
        bool operator() (const int &a, const int &b) {
            return a > b;
        }
    };
};

// LintCode 471 - Top K Frequent Words, Heap, 20190216
class Solution {
public:
    vector<string> topKFrequentWords(vector<string> &words, 
                                     int k) {
        vector<string> results;
        if (words.empty() || k <= 0) {
            return results;
        }
        
        unordered_map<string, int> freqs;
        for (string &word : words) {
            if (!freqs.count(word)) {
                freqs[word] = 0;
            }
            freqs[word]++;
        }
        
        priority_queue<pair<string, int>, 
                       vector<pair<string, int>>, myComp> pq;
        for (pair<const string, int> &item : freqs) {
            pq.push({item.first, item.second});
            if (pq.size() > k) {
                pq.pop();
            }
        }
        
        while (!pq.empty()) {
            results.push_back(pq.top().first);
            pq.pop();
        }
        
        reverse(results.begin(), results.end());
        return results;
    }
    
private:
    struct myComp {
        bool operator() (pair<string, int> a, 
                         pair<string, int> b) {
            if (a.second == b.second) {
                return a.first < b.first;
            }
            return a.second > b.second;
        }
    };
};

// LintCode 401 - Kth Smallest Number in Sorted Matrix, 
// Heap, 20190216
class Solution {
public:
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        if (matrix.empty() || matrix[0].empty()) {
            return -1;
        }
        int m = matrix.size(), n = matrix[0].size();
        if (m * n < k) {
            return -1;
        }
        
        priority_queue<int, vector<int>, myComp> heap;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (heap.size() < k) {
                    heap.push(matrix[i][j]);
                } else {
                    if (matrix[i][j] > heap.top()) {
                        break;
                    }
                    heap.push(matrix[i][j]);
                    heap.pop();
                }
            }
        }
        
        return heap.top();
    }
    
private:
    struct myComp {
        bool operator() (const int &a, const int &b) {
            return a < b;
        }
    };
};

// LintCode 401 - Kth Smallest Number in Sorted Matrix, 
// Binary Search, 20190216
class Solution {
public:
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        
        int left = matrix[0][0];
        int right = matrix[m - 1][n - 1];
        while (left <= right) {
            int mid = left + (right - left) / 2;
            ResultType *result = check(matrix, mid);
            if (result->exist && result->num == k) {
                return mid;
            } else if (result->num < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return left;
    }

private:
    struct ResultType {
        int num;
        bool exist;
        ResultType(bool exist, int num) {
            this->exist = exist;
            this->num = num;
        }
    };
    
    ResultType *check(vector<vector<int>> &matrix, int value) {
        int m = matrix.size(), n = matrix[0].size();
        bool exist = false;
        int num = 0;
        int i = m - 1, j = 0;
        while (i >= 0 && j < n) {
            if (matrix[i][j] == value) {
                exist = true;
            }
            if (matrix[i][j] <= value) {
                num += i + 1;
                j += 1;
            } else {
                i -= 1;
            }
        }
        
        return new ResultType(exist, num);
    }
};

// LeetCode 225 - Implement Stack by Two Queues, Queue, 20190217
class Stack {
private:
    queue<int> q1, q2;
    
    void _moveItems() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
    }
    
public:
    void push(int x) {
        q1.push(x);
    }

    void pop() {
        _moveItems();
        q1.pop();
        swap(q1, q2);
    }

    int top() {
        _moveItems();
        int item = q1.front();
        q1.pop();
        q2.push(item);
        swap(q1, q2);
        return item;
    }

    bool isEmpty() {
        return q1.empty();
    }
};

// LeetCode 232 - Implement Queue by Two Stacks, Stack, 20190217
class MyQueue {
private:
    stack<int> s1, s2;
    
public:
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
    
    int pop() {
        int result = s1.top();
        s1.pop();
        return result;
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return s1.empty();
    }
};

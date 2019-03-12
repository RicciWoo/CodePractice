/******************** Heap ********************/

// Merge k Sorted List, use Heap
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class myComparator {
public:
    bool operator() (const ListNode *n1, const ListNode *n2) {
        return n1->val > n2->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode *, vector<ListNode *>, 
                       myComparator> minHeap;
        for (int i = 0; i < lists.size(); i++)
            if (lists[i]) minHeap.push(lists[i]);
        ListNode *dummy = new ListNode(-1);
        ListNode *curr = dummy;
        while (!minHeap.empty()) {
            curr->next = minHeap.top();
            minHeap.pop();
            curr = curr->next;
            if (curr->next) minHeap.push(curr->next);
        }
        return dummy->next;
    }
};

// Merge k Sorted Arrays, use Heap
class myComp {
public:
    bool operator() (const pair<int, int> &a, 
                     const pair<int, int> &b) {
        return a.first > b.first;
    }
};
class Solution {
public:
    vector<int> mergeKArray(vector<vector<int>> &arrays) {
        int k = arrays.size(), n = arrays[0].size();
        priority_queue<pair<int, int>, 
                       vector<pair<int, int>>, myComp> pq;
        for (int i = 0; i < arrays.size(); i++)
            pq.push({arrays[i][0], i * n});
        vector<int> result;
        while (!pq.empty()) {
            pair<int, int> item = pq.top();
            pq.pop();
            int val = item.first;
            int i = item.second / n, j = item.second % n;
            if (++j < n) pq.push({arrays[i][j], i * n + j});
            result.push_back(val);
        }
        return result;
    }
};

// Sliding Window Maximum, use Heap
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.empty()) return nums;
        vector<int> result(nums.size() - k + 1, 0);
        deque<int> dq;
        for (int i = 0; i < nums.size(); i++) {
            if (!dq.empty() && dq.front() == i - k)
                dq.pop_front();
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) result[i - k + 1] = nums[dq.front()];
        }
        return result;
    }
};

// Kth Largest Element in an Array, use heap
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, myComp> minHeap;
        for (int i = 0; i < k; i++)
            minHeap.push(nums[i]);
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] >= minHeap.top()) {
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }
        return minHeap.top();
    }
};

// Find Median from Data Stream-1, use Heap
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};
class MedianFinder {
private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, myComp> minHeap;
    
public:    
    void addNum(int num) {
        if (!minHeap.empty() && num > minHeap.top())
            minHeap.push(num);
        else
            maxHeap.push(num);
        if (minHeap.size() - maxHeap.size() == 2) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        } else if (maxHeap.size() - minHeap.size() == 2) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
    }
    
    double findMedian() {
        if (minHeap.size() > maxHeap.size())
            return minHeap.top();
        if (maxHeap.size() > minHeap.size())
            return maxHeap.top();
        return (minHeap.top() + maxHeap.top()) / 2.0;
    }
};

// Find Median from Data Stream-2, use Heap
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};
class MedianFinder {
private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, myComp> minHeap;
    
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
        if (minHeap.size() == maxHeap.size())
            return (minHeap.top() + maxHeap.top()) / 2.0;
        return maxHeap.top();
    }
};

// Top N Numbers, use Heap
class myComp {
public:
    bool operator() (const int &a, const int &b) {
        return a > b;
    }
};
class Solution {
public:
    vector<int> topNumbers(vector<vector<int>> &nums) {
        int m = nums.size();
        int n = nums[0].size();
        priority_queue<int, vector<int>, myComp> minHeap;
        for (int i : nums[0]) minHeap.push(i);
        vector<int> list(n, 0);
        for (int i = 1; i < m; i++) {
            for (int j = n - 1; j >= 0; j--) {
                list[j] = minHeap.top();
                minHeap.pop();
            }
            vector<int> curr = nums[i];
            sort(curr.begin(), curr.end(), greater<int>());
            int largest = curr[0];
            for (int j = 0; j < n; j++)
                minHeap.push(largest + list[j]);
            for (int j = 1; j < n; j++) {
                for (int r = 0; r < n; r++) {
                    if (curr[j] + list[r] < minHeap.top())
                        break;
                    minHeap.pop();
                    minHeap.push(curr[j] + list[r]);
                }
            }
        }
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        sort(result.begin(), result.end(), greater<int>());
        return result;
    }
};
















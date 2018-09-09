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


















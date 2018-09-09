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

/******************** Two Pointers ********************/

// LintCode 604 - Window Sum, Two Pointers, 20181125
class Solution {
public:
    vector<int> winSum(vector<int> &nums, int k) {
        if (nums.empty() || k <= 0 || nums.size() < k) {
            return vector<int>();
        }
        
        vector<int> sums(nums.size() - k + 1, 0);
        for (int i = 0; i < k; i++) {
            sums[0] += nums[i];
        }
        for (int i = k; i < nums.size(); i++) {
            sums[i - k + 1] = sums[i - k] - nums[i - k] + nums[i];
        }
        
        return sums;
    }
};

// LintCode 521 - Remove Duplicate Numbers in Array, Two Pointers, 20181125
class Solution {
public:
    int deduplication(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        int j = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[j]) {
                nums[++j] = nums[i];
            }
        }
        
        return j + 1;
    }
};

// LeetCode 876 - Middle of the Linked List, 20181125
// If there are two middle nodes, return the second middle node.
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
    ListNode* middleNode(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
            if (fast != nullptr) {
                fast = fast->next;
            }
        }
        
        return slow;
    }
};

// LintCode 228 - Middle of Linked List, 20181125
// Given 1->2, return the node with value 1.
/**
 * Definition of singly-linked-list:
 * class ListNode {
 * public:
 *     int val;
 *     ListNode *next;
 *     ListNode(int val) {
 *        this->val = val;
 *        this->next = NULL;
 *     }
 * }
 */
class Solution {
public:
    ListNode *middleNode(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
};

// LeetCode 141 - Linked List Cycle, Two Pointers, 20181125
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
    bool hasCycle(ListNode *head) {
        if (head == nullptr) {
            return false;
        }
        
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return true;
    }
};

// LeetCode 142 - Linked List Cycle II, Two Pointers, 20181125
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
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast != slow) {
            if (fast == nullptr || fast->next == nullptr) {
                return nullptr;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        
        slow = head;
        fast = fast->next;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;
    }
};

// LeetCode 160 - Intersection of Two Linked Lists, Two Pointers, 20181125
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        
        // get the tail of list A
        ListNode *tail = headA;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        
        // form a cycle on list B, and find the intersection
        tail->next = headB;
        ListNode *result = _listCycleII(headA);
        
        // break the cycle
        tail->next = nullptr;
        return result;
    }
    
private:
    ListNode *_listCycleII(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head->next;
        
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return nullptr;
            }
            
            slow = slow->next;
            fast = fast->next->next;
        }
        
        slow = head;
        fast = fast->next;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;
    }
};

// LeetCode 283 - Move Zeroes, Two Pointers, 20181125
class Solution {
public:
    void moveZeroes(vector<int> &nums) {
        if (nums.empty()) {
            return;
        }
        
        int j = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                if (i != j) {
                    nums[j] = nums[i];
                }
                j++;
            }
        }
        
        while (j < nums.size()) {
            if (nums[j] != 0) {
                nums[j] = 0;
            }
            j++;
        }
    }
};

// LeetCode 125 - Valid Palindrome, Two Pointers, 20181125
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.empty()) {
            return true;
        }
        
        int left = 0, right = s.size() - 1;
        while (left < right) {            
            if (!isalnum(s[left])) {
                left++;
            } else if (!isalnum(s[right])) {
                right--;
            } else if (tolower(s[left]) != tolower(s[right])) {
                return false;
            } else {
                left++;
                right--;
            }
        }
        
        return true;
    }
};

// LeetCode 680 - Valid Palindrome II, Two Pointers, 20181125
class Solution {
public:
    bool validPalindrome(string s) {
        if (s.size() <= 2) {
            return true;
        }
        
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

// LeetCode 1 - Two Sum, Hash Table, 20181125
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        if (nums.size() < 2) {
            return result;
        }
        
        unordered_map<int, int> hashMap;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (hashMap.count(complement)) {
                result.push_back(i);
                result.push_back(hashMap[complement]);
                return result;
            }
            hashMap.insert({nums[i], i});
        }
        
        return result;
    }
};

// Two Sum III - Data Structure Design, Hash Table, 20181125
class TwoSum {
private:
    unordered_map<int, int> hashMap;

public:    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        hashMap[number]++;
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for (pair<const int, int> p : hashMap) {
            int diff = value - p.first;
            if (hashMap.count(diff)) {
                if (diff != p.first || hashMap[diff] > 1) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

// LeetCode 167 - Two Sum II - Input array is sorted, Two Pointers, 20181125
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;
        if (numbers.size() < 2) {
            return result;
        }
        
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                result.push_back(left + 1);
                result.push_back(right + 1);
                return result;
            }
            if (sum < target){
                left++;
            } else {
                right--;
            }
        }
        
        return result;
    }
};

// LintCode 587 - Two Sum - Unique Pairs, Two Pointers, 20181125
class Solution {
public:
    int twoSum6(vector<int> &nums, int target) {
        if (nums.size() < 2) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        int count = 0;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                count++;
                left++;
                right--;
                
                while (left < right && nums[left] == nums[left - 1]) {
                    left++;
                }
                while (left < right && nums[right] == nums[right + 1]) {
                    right--;
                }
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return count;
    }
};

// LeetCode 15 - 3Sum, Two Pointers, 20181125
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> results;
        if (nums.size() < 3) {
            return results;
        }
        
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i ++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            int target = -nums[i];
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[left] + nums[right];
                if (sum == target) {
                    results.push_back({nums[i], 
                                       nums[left], nums[right]});
                    left++;
                    right--;
                    
                    while (left < right && 
                           nums[left] == nums[left - 1]) {
                        left++;
                    }
                    while (left < right && 
                           nums[right] == nums[right + 1]) {
                        right--;
                    }
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return results;
    }
};

// LeetCode 611 - Valid Triangle Number, Two Pointers, 20181125
class Solution {
public:
    int triangleNumber(vector<int> &nums) {
        if (nums.size() < 3) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        int count = 0;
        for (int i = 2; i < nums.size(); i++) {
            int left = 0, right = i - 1;
            while (left < right) {
                int sum = nums[left] + nums[right];
                if (sum > nums[i]) {
                    count += right - left;
                    right--;
                } else {
                    left++;
                }
            }
        }
        
        return count;
    }
};

// LintCode 609 - Two Sum - Less Than or Equal to Target, Two Pointers, 20181126
class Solution {
public:
    int twoSum5(vector<int> &nums, int target) {
        if (nums.size() < 2) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        int count = 0;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum <= target) {
                count += right - left;
                left++;
            } else {
                right--;
            }
        }
        
        return count;
    }
};

// LintCode 443 - Two Sum - Greater Than Target, Two Pointers, 20181126
class Solution {
public:
    int twoSum2(vector<int> &nums, int target) {
        if (nums.size() < 2) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        int count = 0;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum > target) {
                count += right - left;
                right--;
            } else {
                left++;
            }
        }
        
        return count;
    }
};

// LintCode 533 - Two Sum - Closest to Target, Two Pointers, 20181126
class Solution {
public:
    int twoSumClosest(vector<int> &nums, int target) {
        if (nums.size() < 2) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        int diff = INT_MAX;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum <= target) {
                diff = min(diff, target - sum);
                left++;
            } else {
                diff = min(diff, sum - target);
                right--;
            }
        }
        
        return diff;
    }
};

// LeetCode 16 - 3Sum Closest, Two Pointers, 20181126
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 3) {
            return 0;
        }
        if (nums.size() == 3) {
            return nums[0] + nums[1] + nums[2];
        }
        
        sort(nums.begin(), nums.end());
        int result = 0, minDiff = INT_MAX;
        for (int i = 0; i < nums.size() - 2; i++) {
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                int diff = abs(sum - target);
                if (diff < minDiff) {
                    minDiff = diff;
                    result = sum;
                }
                
                if (sum <= target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return result;
    }
};

// LeetCode 18 - 4Sum, Two Pointers, 20181126
class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> results;
        if (nums.size() < 4) {
            return results;
        }
        
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            for (int j = i + 1; j < nums.size() - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                
                int left = j + 1, right = nums.size() - 1;
                while (left < right) {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        results.push_back({nums[i], nums[j], 
                                           nums[left], nums[right]});
                        left++;
                        right--;
                        
                        while (left < right && 
                               nums[left] == nums[left - 1]) {
                            left++;
                        }
                        while (left < right && 
                               nums[right] == nums[right + 1]) {
                            right--;
                        }
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        
        return results;
    }
};

// LintCode 610 - Two Sum - difference equals to target, Hash Table, 20181126
class Solution {
public:
    vector<int> twoSum7(vector<int> &nums, int target) {
        vector<int> result;
        if (nums.size() < 2) {
            return result;
        }
        
        unordered_map<int, int> hashMap;
        for (int i = 0; i < nums.size(); i++) {
            int sum = nums[i] + target;
            if (hashMap.count(sum)) {
                int index = hashMap[sum];
                result.push_back(index + 1);
                result.push_back(i + 1);
                return result;
            }
            
            int diff = nums[i] - target;
            if (hashMap.count(diff)) {
                int index = hashMap[diff];
                result.push_back(index + 1);
                result.push_back(i + 1);
                return result;
            }
            
            hashMap.insert({nums[i], i});
        }
        
        return result;
    }
};

// LintCode 463 - Sort Integers, Merge Sort, 20181129
class Solution {
public:
    void sortIntegers(vector<int> &A) {
        if (A.empty()) {
            return;
        }
        
        vector<int> temp(A.size(), 0);
        _mergeSort(A, 0, A.size() - 1, temp);
    }
    
private:
    void _mergeSort(vector<int> &A, int start, int end, 
                    vector<int> &temp) {
        if (start >= end) {
            return;
        }
        
        int mid = start + (end - start) / 2;
        _mergeSort(A, start, mid, temp);
        _mergeSort(A, mid + 1, end, temp);
        _merge(A, start, end, temp);
    }
    
    void _merge(vector<int> &A, int start, int end, 
                vector<int> &temp) {
        int leftIndex = start;
        int mid = start + (end - start) / 2;
        int rightIndex = mid + 1;
        int index = leftIndex;
        
        while (leftIndex <= mid && rightIndex <= end) {
            if (A[leftIndex] < A[rightIndex]) {
                temp[index++] = A[leftIndex++];
            } else {
                temp[index++] = A[rightIndex++];
            }
        }
        
        while (leftIndex <= mid) {
            temp[index++] = A[leftIndex++];
        }
        while (rightIndex <= end) {
            temp[index++] = A[rightIndex++];
        }
        
        for (int i = start; i <= end; i++) {
            A[i] = temp[i];
        }
    }
};

// LintCode 464 - Sort Integers II, Quick Sort, 20181129
class Solution {
public:
    void sortIntegers2(vector<int> &nums) {
        if (nums.empty()) {
            return;
        }
        
        _quickSort(nums, 0, nums.size() - 1);
    }
    
private:
    void _quickSort(vector<int> &nums, int start, int end) {
        if (start >= end) {
            return;
        }
        
        int left = start, right = end;
        // get value, not index
        int pivot = nums[start + (end - start) / 2];
        // left <= right, not left < right
        while (left <= right) {
            // nums[left] < pivot, not nums[left] <= pivot
            while (left <= right && nums[left] < pivot) {
                left++;
            }
            // nums[right] > pivot, not nums[right] >= pivot
            while (left <= right && nums[right] > pivot) {
                right--;
            }
            
            if (left <= right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        _quickSort(nums, start, right);
        _quickSort(nums, left, end);
    }
};

// Partition Array
class Solution {
public:
    int partitionArray(vector<int> &nums, int k) {
        if (nums.empty()) {
            return 0;
        }
        
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            while (left <= right && nums[left] < k) {
                left++;
            }
            
            while (left <= right && nums[right] >= k) {
                right--;
            }
            
            if (left <= right) {
                int temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
                left++;
                right--;
            }
        }
        
        return left;
    }
};

// LintCode 461 - Kth Smallest Numbers in Unsorted Array, Quick Select, 20181129
class Solution {
public:
    int kthSmallest(int k, vector<int> &nums) {
        if (nums.empty() || k <= 0 || k > nums.size()) {
            return -1;
        }
        
        return _quickSelect(nums, 0, nums.size() - 1, k);
    }
    
private:
    int _quickSelect(vector<int> &nums, int start, int end, int k) {
        if (start == end) {
            return nums[start];
        }
        
        int left = start, right = end;
        int pivot = nums[start + (end - start) / 2];
        while (left <= right) {
            while (left <= right && nums[left] < pivot) {
                left++;
            }
            
            while (left <= right && nums[right] > pivot) {
                right--;
            }
            
            if (left <= right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        if (start + k - 1 <= right) {
            return _quickSelect(nums, start, right, k);
        }
        if (start + k - 1 >= left) {
            return _quickSelect(nums, left, end, k - (left - start));
        }
        return nums[start + 1];
    }
};

// LintCode 461 - Kth Smallest Numbers in Unsorted Array, Partition, 20181129
class Solution {
public:
    int kthSmallest(int k, vector<int> &nums) {
        if (nums.empty() || k <= 0 || k > nums.size()) {
            return -1;
        }
        
        return _partition(nums, 0, nums.size() - 1, k - 1);
    }
    
private:
    int _partition(vector<int> &nums, int start, int end, int k) {
        if (start == end) {
            return nums[start];
        }
        
        int left = start, right = end;
        int pivot = nums[left + (right - left) / 2];
        while (left <= right) {
            while (left <= right && nums[left] < pivot) {
                left++;
            }
            
            while (left <= right && nums[right] > pivot) {
                right--;
            }
            
            if (left <= right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        if (k <= right) {
            return _partition(nums, start, right, k);
        }
        if (k >= left) {
            return _partition(nums, left, end, k);
        }
        return nums[k];
    }
};

// LeetCode 215 - Kth Largest Element in an Array, Quick Select, 20181129
class Solution {
public:
    int findKthLargest(vector<int> &nums, int k) {
        if (nums.empty()) {
            return -1;
        }
        
        return _quickSelect(nums, 0, nums.size() - 1, k);
    }
    
private:
    int _quickSelect(vector<int> &nums, int start, int end, int k) {
        if (start == end) {
            return nums[start];
        }
        
        int left = start, right = end;
        int pivot = nums[start + (end - start) / 2];
        while (left <= right) {
            while (left <= right && nums[left] > pivot) {
                left++;
            }
            while (left <= right && nums[right] < pivot) {
                right--;
            }
            
            if (left <= right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        if (start + k - 1 <= right) {
            return _quickSelect(nums, start, right, k);
        }
        if (start + k - 1 >= left) {
            return _quickSelect(nums, left, end, k - (left - start));
        }
        return nums[right + 1];
    }
};

// LeetCode 215 - Kth Largest Element in an Array, Partition, 20181129
class Solution {
public:
    int findKthLargest(vector<int> &nums, int k) {
        if (nums.empty()) {
            return -1;
        }
        
        return _partition(nums, 0, nums.size() - 1, k - 1);
    }
    
private:
    int _partition(vector<int> &nums, int start, int end, int k) {
        if (start == end) {
            return nums[start];
        }
        
        int left = start, right = end;
        int pivot = nums[start + (end - start) / 2];
        while (left <= right) {
            while (left <= right && nums[left] > pivot) {
                left++;
            }
            while (left <= right && nums[right] < pivot) {
                right--;
            }
            
            if (left <= right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
        
        if (k <= right) {
            return _partition(nums, start, right, k);
        }
        if (k >= left) {
            return _partition(nums, left, end, k);
        }
        return nums[k];
    }
};

// LeetCode 905 - Sort Array By Parity, Two Pointers, 20181129
class Solution {
public:
    vector<int> sortArrayByParity(vector<int> &A) {
        if (A.empty()) {
            return A;
        }
        
        int left = 0, right = A.size() - 1;
        while (left < right) {
            while (left < right && A[left] % 2 == 0) {
                left++;
            }
            while (left < right && A[right] % 2 == 1) {
                right--;
            }
            
            if (left < right) {
                swap(A[left], A[right]);
                left++;
                right--;
            }
        }
        
        return A;
    }
};

// LintCode 373 - Partition Array by Odd and Even, Two Pointers, 20181129
class Solution {
public:
    void partitionArray(vector<int> &nums) {
        if (nums.empty()) {
            return;
        }
        
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            while (left < right && nums[left] % 2 == 1) {
                left++;
            }
            while (left < right && nums[right] % 2 == 0) {
                right--;
            }
            
            if (left < right) {
                swap(nums[left], nums[right]);
                left++;
                right--;
            }
        }
    }
};

// LintCode 144 - Interleaving Positive and Negative Numbers, Merge Sort, 20181129
class Solution {
public:
    void rerange(vector<int> &A) {
        if (A.empty()) {
            return;
        }
        
        vector<int> pos, neg;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] > 0) {
                pos.push_back(A[i]);
            } else {
                neg.push_back(A[i]);
            }
        }
        
        if (pos.size() > neg.size()) {
            _merge(pos, neg, A);
        } else {
            _merge(neg, pos, A);
        }
    }
    
private:
    void _merge(vector<int> &A, vector<int> &B, 
                vector<int> &result) {
        for (int i = 0; i < B.size(); i++) {
            result[i * 2] = A[i];
            result[i * 2 + 1] = B[i];
        }
        if (A.size() > B.size()) {
            result[result.size() - 1] = A[A.size() - 1];
        }
    }
};

// LintCode 49 - Sort Letters by Case, Two Pointers, 20181129
class Solution {
public:
    void sortLetters(string &chars) {
        if (chars.empty()) {
            return;
        }
        
        int left = 0, right = chars.size() - 1;
        while (left < right) {
            while (left < right && islower(chars[left])) {
                left++;
            }
            while (left < right && isupper(chars[right])) {
                right--;
            }
            
            if (left < right) {
                swap(chars[left], chars[right]);
                left++;
                right--;
            }
        }
    }
};

// LeetCode 75 - Sort Colors, Two Pointers, 20181129
class Solution {
public:
    void sortColors(vector<int> &nums) {
        if (nums.empty()) {
            return;
        }
        
        int left = 0, right = nums.size() - 1;
        int mid = 0;
        while (mid <= right) {
            if (nums[mid] == 0) {
                swap(nums[mid], nums[left]);
                left++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                swap(nums[mid], nums[right]);
                right--;
            }
        }
    }
};

// LintCode 143 - Sort Colors II, Rainbow Sort, 20181129
class Solution {
public:
    void sortColors2(vector<int> &colors, int k) {
        if (colors.empty() || k <= 0) {
            return;
        }
        
        _rainbowSort(colors, 0, colors.size() - 1, 1, k);
    }
    
private:
    void _rainbowSort(vector<int> &colors, int start, int end, 
                      int colorFrom, int colorTo) {
        if (colorFrom >= colorTo) {
            return;
        }
        if (start >= end) {
            return;
        }
        
        int colorMid = colorFrom + (colorTo - colorFrom) / 2;
        int left = start, right = end;
        while (left < right) {
            while (left < right && colors[left] <= colorMid) {
                left++;
            }
            while (left < right && colors[right] > colorMid) {
                right--;
            }
            
            if (left < right) {
                swap(colors[left], colors[right]);
                left++;
                right--;
            }
        }
        
        _rainbowSort(colors, start, right, colorFrom, colorMid);
        _rainbowSort(colors, left, end, colorMid + 1, colorTo);
    }
};

// LintCode 894 - Pancake Sorting, 20181129
class Solution {
public:
    void pancakeSort(vector<int> &array) {
        if (array.empty()) {
            return;
        }
        
        for (int i = array.size(); i > 1; i--) {
            int maxNum = _findMax(array, i);
            if (maxNum != i - 1) {
                // move maximum number to begining
                FlipTool::flip(array, maxNum);
                // move maximum number to the end
                FlipTool::flip(array, i - 1);
            }
        }
    }
    
private:
    int _findMax(vector<int> &array, int n) {
        int maxNum = 0;
        for (int i = 0; i < n; i++) {
            if (array[i] > array[maxNum]) {
                maxNum = i;
            }
        }
        return maxNum;
    }
};

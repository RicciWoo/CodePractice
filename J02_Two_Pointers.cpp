/******************** Two Pointers ********************/

// LintCode 604 - Window Sum
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
        for (int i = 1; i < sums.size(); i++) {
            sums[i] = sums[i - 1]
                      - nums[i - 1] + nums[i + k - 1];
        }
        return sums;
    }
};

// LintCode 521 - Remove Duplicate Numbers in Array
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

// LeetCode 876 - Middle of the Linked List
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
    ListNode *middleNode(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *slow = &dummy;
        ListNode *fast = &dummy;
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

// LintCode 228 - Middle of Linked List
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
    /**
     * @param head: the head of linked list.
     * @return: a middle node of the linked list
     */
    ListNode *middleNode(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }
        
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *fast = &dummy;
        ListNode *slow = &dummy;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
};

// Intersection of Two Linked Lists

// Linked List Cycle

// Linked List Cycle II

// Intersection of Two Linked Lists

// Move Zeros
class Solution {
public:
    /**
     * @param nums: an integer array
     * @return: nothing
     */
    void moveZeroes(vector<int> &nums) {
        int left = 0, right = 0;
        while (right < nums.size()) {
            if (nums[right] != 0) {
                int temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
                left++;
            }
            right++;
        }
    }
};

// Move Zeros
class Solution {
public:
    /**
     * @param nums: an integer array
     * @return: nothing
     */
    void moveZeroes(vector<int> &nums) {
        int left = 0, right = 0;
        while (right < nums.size()) {
            if (nums[right] != 0) {
                if (left != right)
                    nums[left] = nums[right];
                left++;
            }
            right++;
        }
        
        while (left < nums.size()) {
            if (nums[left] != 0) {
                nums[left] = 0;
            }
            left++;
        }
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

// Two Sum III - Data Structure Design
class TwoSum {
public:
    /**
     * @param number: An integer
     * @return: nothing
     */
    void add(int number) {
        m[number]++;
    }

    /**
     * @param value: An integer
     * @return: Find if there exists any pair of numbers which sum is equal to the value.
     */
    bool find(int value) {
        for (pair<const int, int> p : m) {
            int diff = value - p.first;
            if (m.count(diff)) {
                if (diff != p.first || m[diff] > 1) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
private:
    unordered_map<int, int> m;
};

// Two Sum II - Input Array is Sorted
class Solution {
public:
    /**
     * @param nums: an array of Integer
     * @param target: target = nums[index1] + nums[index2]
     * @return: [index1 + 1, index2 + 1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> result;
        if (nums.size() < 2) {
            return result;
        }
        
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            while (left < right && nums[left] + nums[right] < target) {
                left++;
            }
            
            if (left < right && nums[left] + nums[right] == target) {
                result.push_back(left + 1);
                result.push_back(right + 1);
                break;
            }
            
            right--;
        }
        
        return result;
    }
};

// Two Sum - Unique Pairs
class Solution {
public:
    /**
     * @param nums: an array of integer
     * @param target: An integer
     * @return: An integer
     */
    int twoSum6(vector<int> &nums, int target) {
        if (nums.size() < 2) return 0;
        
        sort(nums.begin(), nums.end());
        int count = 0;
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int value = nums[left] + nums[right];
            if (value == target) {
                count++;
                left++;
                right--;
                
                while (left < right && nums[right] == nums[right + 1]) {
                    right--;
                }
                
                while (left < right && nums[left] == nums[left - 1]) {
                    left++;
                }
            } else if (value < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return count;
    }
};

// 3Sum
class Solution {
public:
    /**
     * @param numbers: Give an array numbers of n integer
     * @return: Find all unique triplets in the array which gives the sum of zero.
     */
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> results;
        if (nums.size() < 3) return results;
        
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            int target = -nums[i];
            int left = i + 1, right = n - 1;
            while (left < right) {
                if (nums[left] + nums[right] == target) {
                    results.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;
                    
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                } else if (nums[left] + nums[right] < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return results;
    }
};

// Triangle Count
class Solution {
public:
    /**
     * @param S: A list of integers
     * @return: An integer
     */
    int triangleCount(vector<int> &S) {
        if (S.size() < 3) return 0;
        
        int result = 0;
        sort(S.begin(), S.end());
        
        for (int i = 2; i < S.size(); i++) {
            int left = 0, right = i - 1;
            while (left < right) {
                if (S[left] + S[right] > S[i]) {
                    result += right - left;
                    right--;
                } else {
                    left++;
                }
            }
        }
        
        return result;
    }
};

// Two Sum - Less Than or Equal to Target

// Two Sum - Greater Than Target

// Two Sum - Closest to Target
class Solution {
public:
    /**
     * @param nums: an integer array
     * @param target: An integer
     * @return: the difference between the sum and the target
     */
    int twoSumClosest(vector<int> &nums, int target) {
        if (nums.size() < 2) {
        	return -1;
        }
        
        sort(nums.begin(), nums.end());
        
        int left = 0, right = nums.size() - 1;
        int diff = INT_MAX;
        
        while (left < right) {
            if (nums[left] + nums[right] < target) {
                diff = min(diff, target - nums[left] - nums[right]);
                left++;
            } else {
                diff = min(diff, nums[left] + nums[right] - target);
                right--;
            }
        }
        
        return diff;
    }
};

// 3Sum Closest
class Solution {
public:
    /**
     * @param nums: Give an array numbers of n integer
     * @param target: An integer
     * @return: return the sum of the three integers, the sum closest target.
     */
    int threeSumClosest(vector<int> &nums, int target) {
        if (nums.size() < 3) {
            return -1;
        }
        
        sort(nums.begin(), nums.end());
        
        int bestSum = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size(); i++) {
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (abs(target - sum) < abs(target - bestSum)) {
                    bestSum = sum;
                }
                
                if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return bestSum;
    }
};

// 4Sum

// Two Sum - difference equals to target

// Partition Array
class Solution {
public:
    /**
     * @param nums: The integer array you should partition
     * @param k: An integer
     * @return: The index after partition
     */
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

// Kth Smallest Numbers in Unsorted Array (Quick Select)
class Solution {
public:
    /**
     * @param k: An integer
     * @param nums: An integer array
     * @return: kth smallest element
     */
    int kthSmallest(int k, vector<int> &nums) {
        if (nums.empty() || k <= 0 || k > nums.size()) {
            return -1;
        }
        
        return _quickSelect(nums, 0, nums.size() - 1, k - 1);
    }
    
private:
    int _quickSelect(vector<int> &nums, int start, int end, int k) {
        if (start > end || k < start || k > end) {
            return -1;
        }
        
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
                int temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
                left++;
                right--;
            }
        }
        
        if (k <= right) {
            return _quickSelect(nums, start, right, k);
        }
        if (k >= left) {
            return _quickSelect(nums, left, end, k);
        }
        return nums[k];
    }
};

// Kth Largest Element (Quick Select)
class Solution {
public:
    /**
     * @param k: An integer
     * @param nums: An array
     * @return: the Kth largest element
     */
    int kthLargestElement(int k, vector<int> &nums) {
        if (nums.empty() || k <= 0 || k > nums.size()) {
            return -1;
        }
        
        return _partition(nums, 0, nums.size() - 1, nums.size() - k);
    }
    
private:
    int _partition(vector<int> &nums, int start, int end, int k) {
        if (start > end || k < start || k > end) {
            return -1;
        }
        
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
                int temp = nums[left];
                nums[left] = nums[right];
                nums[right] = temp;
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

// Partition Array by Odd and Even

// Interleaving Positive and Negative Numbers

// Sort Letters by Case

// Sort Colors
class Solution {
public:
    /**
     * @param nums: A list of integer which is 0, 1 or 2 
     * @return: nothing
     */
    void sortColors(vector<int> &nums) {
        if (nums.empty()) {
            return;
        }
        
        int left = 0, right = nums.size() - 1;
        int middle = 0;
        
        while (middle <= right) {
            if (nums[middle] == 0) {
                swap(nums[middle], nums[left]);
                left++;
                middle++;
            } else if (nums[middle] == 1) {
                middle++;
            } else {
                swap(nums[middle], nums[right]);
                right--;
            }
        }
    }
};

// Sort Colors II (Rainbow Sort)
class Solution {
public:
    /**
     * @param colors: A list of integer
     * @param k: An integer
     * @return: nothing
     */
    void sortColors2(vector<int> &colors, int k) {
        if (colors.empty() || k < 1) {
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
        while (left <= right) {
            while (left <= right && colors[left] <= colorMid) {
                left++;
            }
            
            while (left <= right && colors[right] > colorMid) {
                right--;
            }
            
            if (left <= right) {
                int temp = colors[left];
                colors[left] = colors[right];
                colors[right] = temp;
                left++;
                right--;
            }
        }
        
        _rainbowSort(colors, start, right, colorFrom, colorMid);
        _rainbowSort(colors, left, end, colorMid + 1, colorTo);
    }
};

// Pancake Sort

// Sort Integers II (QuickSort)
class Solution {
public:
    /**
     * @param nums: an integer array
     * @return: nothing
     */
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
        int pivot = nums[start + (end - start) / 2];
        while (left <= right) {
            while (left <= right && nums[left] < pivot) {
                left++;
            }
            
            while (left <= right && nums[right] > pivot) {
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
        
        _quickSort(nums, start, right);
        _quickSort(nums, left, end);
    }
};

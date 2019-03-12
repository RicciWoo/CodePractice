/******************** Interval, Array, Matrix, Binary Indexed Tree ********************/

// LintCode 6 - Merge Two Sorted Arrays, Merge Sort, 20190217
class Solution {
public:
    vector<int> mergeSortedArray(vector<int> &A, vector<int> &B) {
        if (A.empty() || B.empty()) {
            return vector<int>();
        }
        
        vector<int> result(A.size() + B.size());
        int i = 0, j = 0, index = 0;
        while (i < A.size() && j < B.size()) {
            if (A[i] < B[j]) {
                result[index++] = A[i++];
            } else {
                result[index++] = B[j++];
            }
        }
        
        while (i < A.size()) {
            result[index++] = A[i++];
        }
        while (j < B.size()) {
            result[index++] = B[j++];
        }
        
        return result;
    }
};

// LeetCode 88 - Merge Sorted Array, Merge Sort, 20190217
class Solution {
public:
    void merge(vector<int>& nums1, int m, 
               vector<int>& nums2, int n) {
        int ia = m - 1, ib = n - 1, icur = m + n - 1;
        while (ia >= 0 && ib >= 0) {
            if (nums1[ia] >= nums2[ib]) {
                nums1[icur--] = nums1[ia--];
            } else {
                nums1[icur--] = nums2[ib--];
            }
        }
        
        while (ib >= 0) {
            nums1[icur--] = nums2[ib--];
        }
    }
};

// LintCode 839 - Merge Two Sorted Interval Lists, Merge Sort, 20190217
/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */
class Solution {
public:
    vector<Interval> mergeTwoInterval(vector<Interval> &list1, 
                                      vector<Interval> &list2) {
        vector<Interval> results;
        if (list1.empty() && list2.empty()) {
            return results;
        }

        Interval *last = nullptr, *curr = nullptr;
        int i = 0, j = 0;
        while (i < list1.size() && j < list2.size()) {
            if (list1[i].start < list2[j].start) {
                curr = &list1[i];
                i++;
            } else {
                curr = &list2[j];
                j++;
            }
            
            last = _merge(last, curr, results);
        }
        
        while (i < list1.size()) {
            last = _merge(last, &list1[i], results);
            i++;
        }
        while (j < list2.size()) {
            last = _merge(last, &list2[j], results);
            j++;
        }
        
        results.push_back(*last);
        return results;
    }
    
private:
    Interval *_merge(Interval *last, Interval *curr, 
                    vector<Interval> &results) {
        if (last == nullptr) {
            return curr;
        }
        
        if (curr->start > last->end) {
            results.push_back(*last);
            return curr;
        }
        
        last->end = max(last->end, curr->end);
        return last;
    }
};

// LintCode 486 - Merge K Sorted Arrays, Merge Sort, 20190217
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

// LintCode 577 - Merge K Sorted Interval Lists, 20190217
/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */
class Solution {
public:
    vector<Interval> mergeKSortedIntervalLists(
                        vector<vector<Interval>> &intervals) {
        vector<Interval> result;
        if (intervals.empty()) {
            return result;
        }
        
        priority_queue<Element *, vector<Element *>, myComp> heap;
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i].empty()) {
                continue;
            }
            Element *elem = new Element(i, 0, &intervals[i][0]);
            heap.push(elem);
        }
        
        while (!heap.empty()) {
            Element *elem = heap.top();
            heap.pop();
            result.push_back(*elem->interval);
            elem->col++;
            if (elem->col < intervals[elem->row].size()) {
                elem->interval = &intervals[elem->row][elem->col];
                heap.push(elem);
            }
        }
        
        return _merge(result);;
    }
    
private:
    vector<Interval> _merge(vector<Interval> &intervals) {
        if (intervals.size() <= 1) {
            return intervals;
        }
        
        vector<Interval> result;
        int start = intervals[0].start;
        int end = intervals[0].end;
        for (Interval &interval : intervals) {
            if (interval.start <= end) {
                end = max(end, interval.end);
            } else {
                result.push_back(Interval(start, end));
                start = interval.start;
                end = interval.end;
            }
        }
        result.push_back(Interval(start, end));
        return result;
    }
    
private:
    struct Element {
        int row, col;
        Interval *interval;
        Element(int row, int col, Interval *interval) {
            this->row = row;
            this->col = col;
            this->interval = interval;
        }
    };
    
    struct myComp {
        bool operator() (const Element *a, const Element *b) {
            return a->interval->start > b->interval->start;
        }
    };
};

// LeetCode 349 - Intersection of Two Arrays, Two Pointers, 20190217
class Solution {
public:
    vector<int> intersection(vector<int> &nums1, 
                             vector<int> &nums2) {
        vector<int> results;
        if (nums1.empty() || nums2.empty()) {
            return results;
        }
        
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                if (results.empty() || 
                    results[results.size() - 1] != nums1[i]) {
                    results.push_back(nums1[i]);
                }
                i++;
                j++;
            } else if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
        }
        
        return results;
    }
};

// LeetCode 349 - Intersection of Two Arrays, Hash Table, 20190217
class Solution {
public:
    vector<int> intersection(vector<int> &nums1, 
                             vector<int> &nums2) {
        vector<int> results;
        if (nums1.empty() || nums2.empty()) {
            return results;
        }
        
        unordered_set<int> set1;
        for (int i = 0; i < nums1.size(); i++) {
            set1.insert(nums1[i]);
        }
        
        unordered_set<int> set2;
        for (int i = 0; i < nums2.size(); i++) {
            if (set1.count(nums2[i])) {
                set2.insert(nums2[i]);
            }
        }
        
        results.insert(results.end(), 
                       set2.begin(), set2.end());
        return results;
    }
};

// LeetCode 350 - Intersection of Two Arrays II, Two Pointers, 20190217
class Solution {
public:
    vector<int> intersect(vector<int> &nums1, 
                          vector<int> &nums2) {
        vector<int> results;
        if (nums1.empty() || nums2.empty()) {
            return results;
        }
        
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                results.push_back(nums1[i]);
                i++;
                j++;
            } else if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
        }
        
        return results;
    }
};

// LeetCode 350 - Intersection of Two Arrays II, Hash Table, 20190217
class Solution {
public:
    vector<int> intersect(vector<int> &nums1, 
                          vector<int> &nums2) {
        vector<int> results;
        if (nums1.empty() || nums2.empty()) {
            return results;
        }
        
        unordered_map<int, int> hashmap;
        for (int i = 0; i < nums1.size(); i++) {
            if (!hashmap.count(nums1[i])) {
                hashmap[nums1[i]] = 0;
            }
            hashmap[nums1[i]]++;
        }
        
        for (int i = 0; i < nums2.size(); i++) {
            if (hashmap.count(nums2[i])) {
                results.push_back(nums2[i]);
                hashmap[nums2[i]]--;
                if (hashmap[nums2[i]] == 0) {
                    hashmap.erase(nums2[i]);
                }
            }
        }
        
        return results;
    }
};

// LintCode 793 - Intersection of Arrays, Hash Table, 20190218
class Solution {
public:
    int intersectionOfArrays(vector<vector<int>> &arrs) {
        if (arrs.empty()) {
            return 0;
        }
        
        unordered_map<int, int> hashmap;
        for (int i = 0; i < arrs.size(); i++) {
            for (int j = 0; j <arrs[i].size(); j++) {
                hashmap[arrs[i][j]]++;
            }
        }
        
        int result = 0;
        for (pair<const int, int> &item : hashmap) {
            if (item.second == arrs.size()) {
                result++;
            }
        }
        
        return result;
    }
};

// LeetCode 311 - Sparse Matrix Multiplication, 20190218
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>> &A, 
                                 vector<vector<int>> &B) {
        int m = A.size(), t = A[0].size(), n = B[0].size();
        vector<vector<int>> C(m, vector<int>(n, 0));
        
        vector<vector<int>> col(t);
        for (int k = 0; k < t; k++) {
            for (int j = 0; j < n; j++) {
                if (B[k][j] != 0) {
                    col[k].push_back(j);
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < t; k++) {
                if (A[i][k] == 0) {
                    continue;
                }
                for (int j : col[k]) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        
        return C;
    }
};

// LeetCode 4 - Median of two Sorted Arrays, Binary Search, 20190217
class Solution {
public:
    double findMedianSortedArrays(vector<int> &nums1, 
                                  vector<int> &nums2) {
        int n = nums1.size() + nums2.size();
        if (n % 2 == 0) {
            return (_findKth(nums1, 0, nums2, 0, n / 2) + 
                    _findKth(nums1, 0, nums2, 0, n / 2 + 1)) / 2.;
        }
        return _findKth(nums1, 0, nums2, 0, n / 2 + 1);
    }
    
private:
    double _findKth(vector<int> &A, int startOfA, 
                    vector<int> &B, int startOfB, int k) {
        if (startOfA >= A.size()) {
            return B[startOfB + k - 1];
        }
        if (startOfB >= B.size()) {
            return A[startOfA + k - 1];
        }
        
        if (k == 1) {
            return min(A[startOfA], B[startOfB]);
        }
        
        int halfKthOfA = startOfA + k / 2 - 1 < A.size() ? 
            A[startOfA + k / 2 - 1] : INT_MAX;
        int halfKthOfB = startOfB + k / 2 - 1 < B.size() ? 
            B[startOfB + k / 2 - 1] : INT_MAX;
        if (halfKthOfA < halfKthOfB) {
            return _findKth(A, startOfA + k / 2, 
                            B, startOfB, k - k / 2);
        } else {
            return _findKth(A, startOfA, 
                            B, startOfB + k / 2, k - k / 2);
        }
    }
};

// LintCode 931 - Median of K Sorted Arrays, Binary Search, 20190218
class Solution {
public:
    double findMedian(vector<vector<int>> &nums) {
        int n = _getTotal(nums);
        if (n == 0) {
            return 0.;
        }
        
        if (n % 2 != 0) {
            return (double)_findKth(nums, n / 2 + 1);
        }
        return ((double)_findKth(nums, n / 2) + 
                (double)_findKth(nums, n / 2 + 1)) / 2.;
    }
    
private:
    int _getTotal(vector<vector<int>> &nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i].size();
        }
        return sum;
    }
    
    int _findKth(vector<vector<int>> &nums, int k) {
        int start = 0, end = INT_MAX;
        
        // find the last number x that >= k numbers are >= x
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (_getGTE(nums, mid) >= k) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (_getGTE(nums, start) >= k) {
            return start;
        }
        return end;
    }
    
    // get how many numbers greater than or equal to val in 2d array
    int _getGTE(vector<vector<int>> &nums, int val) {
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += _getGTE(nums[i], val);
        }
        return sum;
    }
    
    // get how many numbers greater than or equal to val in an array
    int _getGTE(vector<int> &nums, int val) {
        if (nums.empty()) {
            return 0;
        }
        
        // find first element >= val
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] >= val) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (nums[start] >= val) {
            return nums.size() - start;
        }
        if (nums[end] >= val) {
            return nums.size() - end;
        }
        return 0;
    }
};

// LeetCode 53 - Maximum Subarray, Prefix Sum, 20190217
class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int maxSum = INT_MIN, sum = 0, minSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            maxSum = max(maxSum, sum - minSum);
            minSum = min(minSum, sum);
        }
        
        return maxSum;
    }
};

// LintCode 44 - Minimum Subarray, Prefix Sum, 20190217
class Solution {
public:
    int minSubArray(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int maxSum = INT_MIN, sum = 0, minSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += -nums[i];
            maxSum = max(maxSum, sum - minSum);
            minSum = min(minSum, sum);
        }
        
        return -maxSum;
    }
};

// LintCode 138 - Subarray Sum, Prefix Sum, 20190217
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

// LintCode 139 - Subarray Sum Closest, Sort, 20190217
class Solution {
public:
    vector<int> subarraySumClosest(vector<int> &nums) {
        vector<int> results(2);
        if (nums.empty()) {
            return results;
        }
        if (nums.size() == 1) {
            results[0] = results[1] = 0;
            return results;
        }
        
        vector<Node> s;
        s.push_back(Node(0, -1));
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            s.push_back(Node(sum, i));
        }
        sort(s.begin(), s.end(), myComp());

        int ans = INT_MAX;
        for (int i = 1; i < s.size(); i++) {
            if (abs(s[i].value - s[i - 1].value) < ans) {
                ans = abs(s[i].value - s[i - 1].value);
                results[0] = min(s[i - 1].pos, s[i].pos) + 1;
                results[1] = max(s[i - 1].pos, s[i].pos);
            }
        }
        
        return results;
    }
    
private:
    struct Node {
        int value, pos;
        Node(int value, int pos) {
            this->value = value;
            this->pos = pos;
        }
    };
    
    struct myComp {
        bool operator() (const Node &a, const Node &b) {
            return a.value < b.value;
        }
    };
};

// LeetCode 121 - Best Time to Buy and Sell Stock, Prefix Sum, 20190218
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        if (prices.size() < 2) {
            return 0;
        }
        
        int minPrice = INT_MAX, profit = 0;
        for (int price : prices) {
            minPrice = min(minPrice, price);
            profit = max(profit, price - minPrice);
        }
        
        return profit;
    }
};

// LintCode 405 - Submatrix Sum, Prefix Sum, 20190219
class Solution {
public:
    vector<vector<int>> submatrixSum(vector<vector<int>> &matrix) {
        vector<vector<int>> result(2, vector<int>(2, 0));
        if (matrix.empty() || matrix[0].empty()) {
            return result;
        }
        
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> sum(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum[i + 1][j + 1] = matrix[i][j] + sum[i + 1][j] + 
                                    sum[i][j + 1] - sum[i][j];
            }
        }
        
        for (int l = 0; l < m; l++) {
            for (int h = l + 1; h <= m; h++) {
                unordered_map<int, int> map;
                for (int j = 0; j <= n; j++) {
                    int diff = sum[h][j] - sum[l][j];
                    if (map.count(diff)) {
                        int k = map[diff];
                        result[0][0] = l;
                        result[0][1] = k;
                        result[1][0] = h - 1;
                        result[1][1] = j - 1;
                        return result;
                    } else {
                        map[diff] = j;
                    }
                }
            }
        }
        
        return result;
    }
};

// LintCode 944 - Maximum Submatrix, Prefix Sum, 20190219
class Solution {
public:
    int maxSubmatrix(vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> prefixColSum(n + 1, vector<int>(m, 0));
        _getPrefixColSum(matrix, prefixColSum);
        
        int maxSum = INT_MIN;
        for (int up = 0; up < n; up++) {
            for (int down = up; down < n; down++) {
                vector<int> arr(m);
                _compression(matrix, up, down, prefixColSum, arr);
                maxSum = max(maxSum, _maximumSubarray(m, arr));
            }
        }
        
        return maxSum;
    }
    
private:
    void _getPrefixColSum(vector<vector<int>> &matrix, 
                          vector<vector<int>> &prefixColSum) {
        int n = matrix.size(), m = matrix[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                prefixColSum[i + 1][j] = prefixColSum[i][j] + 
                                         matrix[i][j];
            }
        }
    }

    void _compression(vector<vector<int>> &matrix, int up, int down, 
                   vector<vector<int>> &prefixColSum, 
                   vector<int> &arr) {
        int m = matrix[0].size();
        for (int i = 0; i < m; i++) {
            arr[i] = prefixColSum[down + 1][i] - prefixColSum[up][i];
        }
    }

    int _maximumSubarray(int m, vector<int> &arr) {
        int minSum = 0, maxSum = INT_MIN, sum = 0;
        
        for (int i = 0; i < m; i++) {
            sum += arr[i];
            maxSum = max(maxSum, sum - minSum);
            minSum = min(minSum, sum);
        }
        
        return maxSum;
    }
};

// LeetCode 303 - Range Sum Query - Immutable, Prefix Sum, 20190219
class NumArray {
private:
    vector<int> prefix;

public:
    NumArray(vector<int> nums) {
        prefix = vector<int>(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
    int sumRange(int i, int j) {
        return prefix[j + 1] - prefix[i];
    }
};

// LeetCode 303 - Range Sum Query - Immutable, Segment Tree, 20190219
class NumArray {
public:
    NumArray(vector<int> nums) {
        if (nums.empty()) {
            return;
        }
        
        root = _build(nums, 0, nums.size() - 1);
    }
    
    int sumRange(int i, int j) {
        if (root == nullptr || i > j) {
            return 0;
        }
        
        return _query(root, i, j);
    }
    
private:
    struct SegmentTreeNode {
        int start, end, sum;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(int start, int end, int sum) {
            this->start = start;
            this->end = end;
            this->sum = sum;
            this->left = this->right = nullptr;
        }
    };
    
    SegmentTreeNode *root = nullptr;
    
    SegmentTreeNode *_build(vector<int> &nums, int start, int end) {
        SegmentTreeNode *root = new SegmentTreeNode(start, end, nums[start]);
        if (start == end) {
            return root;
        }
        
        int mid = start + (end - start) / 2;
        root->left = _build(nums, start, mid);
        root->right = _build(nums, mid + 1, end);
        root->sum = root->left->sum + root->right->sum;
        return root;
    }
    
    int _query(SegmentTreeNode *root, int start, int end) {
        if (start <= root->start && root->end <= end) {
            return root->sum;
        }
        
        int mid = root->start + (root->end - root->start) / 2;
        int result = 0;
        if (start <= mid) {
            result += _query(root->left, start, end);
        }
        if (mid < end) {
            result += _query(root->right, start, end);
        }
        
        return result;
    }
};

// LeetCode 304 - Range Sum Query 2D - Immutable, Prefix Sum, 20190219
class NumMatrix {
private:
    vector<vector<int>> dp;
    
public:
    NumMatrix(vector<vector<int>> matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }
        int n = matrix.size(), m = matrix[0].size();
        
        dp = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                dp[r + 1][c + 1] = matrix[r][c] + dp[r + 1][c]
                                   + dp[r][c + 1] - dp[r][c];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2 + 1][col2 + 1] - dp[row1][col2 + 1]
               - dp[row2 + 1][col1] + dp[row1][col1];
    }
};

// LeetCode 307 - Range Sum Query Mutable, Prefix Sum, 20190219
class NumArray {
public:
    NumArray(vector<int> nums) {
        arr = vector<int>(nums.size(), 0);
        bit = vector<int>(nums.size() + 1, 0);
        
        for (int i = 0; i < nums.size(); i++) {
            update(i, nums[i]);
        }
    }
    
    void update(int index, int val) {
        int delta = val - arr[index];
        arr[index] = val;
        
        for (int i = index + 1; i <= arr.size(); i += _lowbit(i)) {
            bit[i] += delta;
        }
    }
    
    int sumRange(int i, int j) {
        return _getPrefixSum(j) - _getPrefixSum(i - 1);
    }
    
private:
    vector<int> arr, bit;
    
    int _lowbit(int x) {
        return x & (-x);
    }
    
    int _getPrefixSum(int index) {
        int sum = 0;
        for (int i = index + 1; i > 0; i -= _lowbit(i)) {
            sum += bit[i];
        }
        return sum;
    }
};

// LeetCode 307 - Range Sum Query Mutable, Prefix Sum, 20190219
class NumArray {
public:
    NumArray(vector<int> nums) {
        if (nums.empty()) {
            return;
        }
        
        root = _build(nums, 0, nums.size() - 1);
    }
    
    void update(int i, int val) {
        if (root == nullptr || 
            i < root->start || i > root->end) {
            return;
        }
        
        _modify(root, i, val);
    }
    
    int sumRange(int i, int j) {
        if (root == nullptr || i > j) {
            return 0;
        }
        
        return _query(root, i, j);
    }
    
private:
    struct SegmentTreeNode {
        int start, end, sum;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(int start, int end, int sum) {
            this->start = start;
            this->end = end;
            this->sum = sum;
            this->left = this->right = nullptr;
        }
    };
    
    SegmentTreeNode *root = nullptr;
    
    SegmentTreeNode *_build(vector<int> &nums, int start, int end) {
        SegmentTreeNode *root = new SegmentTreeNode(start, end, nums[start]);
        if (start == end) {
            return root;
        }
        
        int mid = start + (end - start) / 2;
        root->left = _build(nums, start, mid);
        root->right = _build(nums, mid + 1, end);
        root->sum = root->left->sum + root->right->sum;
        return root;
    }
    
    int _query(SegmentTreeNode *root, int start, int end) {
        if (start <= root->start && root->end <= end) {
            return root->sum;
        }
        
        int mid = root->start + (root->end - root->start) / 2;
        int result = 0;
        if (start <= mid) {
            result += _query(root->left, start, end);
        }
        if (mid < end) {
            result += _query(root->right, start, end);
        }
        
        return result;
    }
    
    void _modify(SegmentTreeNode *root, int index, int value) {
        if (root->start == index && index == root->end) {
            root->sum = value;
            return;
        }
        
        int mid = root->start + (root->end - root->start) / 2;
        if (root->start <= index && index <= mid) {
            _modify(root->left, index, value);
        }
        if (mid < index && index <= root->end) {
            _modify(root->right, index, value);
        }
        root->sum = root->left->sum + root->right->sum;
    }
};

// LeetCode 308 - Range Sum Query 2D Mutable, Binary Indexed Tree, 20190219
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        m = matrix.size();
        n = matrix[0].size();
        arr = vector<vector<int>>(m, vector<int>(n, 0));
        bit = vector<vector<int>>(m + 1, vector<int>(n + 1));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                update(i, j, matrix[i][j]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        int delta = val - arr[row][col];
        arr[row][col] = val;
        
        for (int i = row + 1; i <= m; i += _lowbit(i)) {
            for (int j = col + 1; j <= n; j += _lowbit(j)) {
                bit[i][j] += delta;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return _prefixSum(row2, col2)
               - _prefixSum(row2, col1 - 1)
               - _prefixSum(row1 - 1, col2)
               + _prefixSum(row1 - 1, col1 - 1);
    }
    
private:
    vector<vector<int>> arr, bit;
    int m, n;
    
    int _lowbit(int x) {
        return x & (-x);
    }
    
    int _prefixSum(int row, int col) {
        int sum = 0;
        for (int i = row + 1; i > 0; i -= _lowbit(i)) {
            for (int j = col + 1; j > 0; j -= _lowbit(j)) {
                sum += bit[i][j];
            }
        }
        return sum;
    }
};

// LintCode 249 - Count of Smaller Number before itself, Segment Tree, 20190219
class Solution {
public:
    vector<int> countOfSmallerNumberII(vector<int> &A) {
        vector<int> results;
        if (A.empty()) {
            return results;
        }
        
        SegmentTree *st = new SegmentTree();
        SegTreeNode *root = st->build(0, 10000);
        for (int i : A) {
            int result = st->query(root, 0, i - 1);
            st->modify(root, i, 1);
            results.push_back(result);
        }
        
        return results;
    }
    
private:
    struct SegTreeNode {
        int start, end, count;
        SegTreeNode *left, *right;
        SegTreeNode(int start, int end, int count) {
            this->start = start;
            this->end = end;
            this->count = count;
            this->left = this->right = nullptr;
        }
    };
    
    struct SegmentTree {
        SegTreeNode *build(int start, int end) {
            if (start > end) {
                return nullptr;
            }
            
            SegTreeNode *root = new SegTreeNode(start, end, 0);
            if (start == end) {
                return root;
            }
            
            int mid = start + (end - start) / 2;
            root->left = build(start, mid);
            root->right = build(mid + 1, end);
            return root;
        }
        
        int query(SegTreeNode *root, int start, int end) {
            if (root == nullptr || start > end) {
                return 0;
            }
            if (start <= root->start && root->end <= end) {
                return root->count;
            }
            
            int mid = root->start + (root->end - root->start) / 2;
            int result = 0;
            if (start <= mid) {
                result += query(root->left, start, end);
            }
            if (mid < end) {
                result += query(root->right, start, end);
            }
            
            return result;
        }
        
        void modify(SegTreeNode *root, int index, int value) {
            if (root == nullptr || 
                index < root->start || index > root->end) {
                return;
            }
            if (root->start == index && index == root->end) {
                root->count += value;
                return;
            }
            
            int mid = root->start + (root->end - root->start) / 2;
            if (root->start <= index && index <= mid) {
                modify(root->left, index, value);
            }
            if (mid < index && index <= root->end) {
                modify(root->right, index, value);
            }
            
            root->count = root->left->count + root->right->count;
        }
    };
};

// LeetCode 315 - Count of Smaller Numbers After Self, Segment Tree, 20190219
class Solution {
public:
    vector<int> countSmaller(vector<int> &nums) {
        vector<int> results;
        if (nums.empty()) {
            return results;
        }
        
        SegmentTree *st = new SegmentTree();
        SegmentTreeNode *root = st->build(nums, -10000, 10000);
        for (int i = nums.size() - 1; i >= 0; i--) {
            int result = st->query(root, -10000, nums[i] - 1);
            st->modify(root, nums[i], 1);
            results.push_back(result);
        }
        
        reverse(results.begin(), results.end());
        return results;
    }
    
private:
    struct SegmentTreeNode {
        int start, end, count;
        SegmentTreeNode *left, *right;
        SegmentTreeNode(int start, int end, int count) {
            this->start = start;
            this->end = end;
            this->count = count;
            this->left = this->right = nullptr;
        }
    };

    struct SegmentTree {
        SegmentTreeNode *build(vector<int> &nums, int start, int end) {
            if (nums.empty() || start > end) {
                return nullptr;
            }

            SegmentTreeNode *root = new SegmentTreeNode(start, end, 0);
            if (start == end) {
                return root;
            }

            int mid = start + (end - start) / 2;
            root->left = build(nums, start, mid);
            root->right = build(nums, mid + 1, end);
            return root;
        }

        int query(SegmentTreeNode *root, int start, int end) {
            if (root == nullptr || start > end) {
                return 0;
            }
            if (start <= root->start && root->end <= end) {
                return root->count;
            }

            int mid = root->start + (root->end - root->start) / 2;
            int result = 0;
            if (start <= mid) {
                result += query(root->left, start, end);
            }
            if (mid < end) {
                result += query(root->right, start, end);
            }

            return result;
        }

        void modify(SegmentTreeNode *root, int index, int value) {
            if (root == nullptr || 
                index < root->start || index > root->end) {
                return;
            }
            if (root->start == index && index == root->end) {
                root->count += value;
                return;
            }

            int mid = root->start + (root->end - root->start) / 2;
            if (root->start <= index && index <= mid) {
                modify(root->left, index, value);
            }
            if (mid < index && index <= root->end) {
                modify(root->right, index, value);
            }

            root->count = root->left->count + root->right->count;
        }
    };
};

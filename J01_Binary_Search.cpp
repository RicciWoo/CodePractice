/******************** Binary Search ********************/

// LintCode 704 - Binary Search, Binary Search, 20181205
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size();
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
         }
        
        if (nums[start] == target) {
            return start;
        }
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
};

// LintCode 14 - First Position of Target, Binary Search, 20181205
class Solution {
public:
    int binarySearch(vector<int> &nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[start] == target) {
            return start;
        }
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
};

// LintCode 458 - Last Position of Target, Binary Search, 20181205
class Solution {
public:
    int lastPosition(vector<int> &nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] <= target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[end] == target) {
            return end;
        }
        if (nums[start] == target) {
            return start;
        }
        return -1;
    }
};

// LeetCode 34 - Find First and Last Position of Element in Sorted Array, 
// Binary Search, 20181205
class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> result(2, -1);
        if (nums.empty()) {
            return result;
        }
        
        result[0] = _findFirstPos(nums, target);
        result[1] = _findLastPos(nums, target);
        
        return result;
    }
    
private: 
    int _findFirstPos(vector<int> &nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[start] == target) {
            return start;
        }
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
    
    int _findLastPos(vector<int> &nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] <= target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[end] == target) {
            return end;
        }
        if (nums[start] == target) {
            return start;
        }
        return -1;
    }
};

// LintCode 462 - Total Occurrence of Target, Binary Search, 20181205
class Solution {
public:
    int totalOccurrence(vector<int> &A, int target) {
        if (A.empty()) {
            return 0;
        }
        
        int first = _findFirstPos(A, target);
        int last = _findLastPos(A, target);
        
        if (first < 0) {
            return 0;
        }
        return last - first + 1;
    }
    
private:
    int _findFirstPos(vector<int> &A, int target) {
        int start = 0, end = A.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (A[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (A[start] >= target) {
            return start;
        }
        if (A[end] >= target) {
            return end;
        }
        return -1;
    }
    
    int _findLastPos(vector<int> &A, int target) {
        int start = 0, end = A.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (A[mid] <= target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (A[end] <= target) {
            return end;
        }
        if (A[start] <= target) {
            return start;
        }
        return -1;
    }
};

// LeetCode 35 - Search Insert Position, Binary Search, 20181205
class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        if (nums.empty()) {
            return 0;
        }
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[start] >= target) {
            return start;
        }
        if (nums[end] >= target) {
            return end;
        }
        return nums.size();
    }
};

// LeetCode 278 - First Bad Version, Binary Search, 20181205
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);
class Solution {
public:
    int firstBadVersion(int n) {
        if (n <= 0) {
            return 0;
        }
        
        int start = 1, end = n;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (isBadVersion(mid)) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (isBadVersion(start)) {
            return start;
        }
        return end;
    }
};

// LeetCode 658 - Find K Closest Elements, Binary Search, 20181205
class Solution {
public:
    vector<int> findClosestElements(vector<int> &arr, 
                                    int k, int x) {
        if (arr.empty()) {
            return vector<int>();
        }
        
        int left = _findLowerClosest(arr, x);
        int right = left + 1;
        for (int i = 0; i < k; i++) {
            if (_leftIsCloser(arr, x, left, right)) {
                left--;
            } else {
                right++;
            }
        }
        
        vector<int> result(arr.begin() + left + 1, 
                           arr.begin() + right);
        return result;
    }
    
private:
    int _findLowerClosest(vector<int> &arr, int x) {
        int start = 0, end = arr.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (arr[mid] < x) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (arr[end] < x) {
            return end;
        }
        if (arr[start] < x) {
            return start;
        }
        return -1;
    }
    
    bool _leftIsCloser(vector<int> &arr, int x, 
                       int left, int right) {
        if (left < 0) {
            return false;
        }
        if (right >= arr.size()) {
            return true;
        }
        return x - arr[left] <= arr[right] - x;
    }
};

// LeetCode 702 - Search in a Sorted Array of Unknown Size, Binary Search, 20181205
// Forward declaration of ArrayReader class.
class ArrayReader;
class Solution {
public:
    int search(const ArrayReader &reader, int target) {
        int index = 0;
        while (reader.get(index) < target) {
            index = index * 2 + 1;
        }
        
        int start = 0, end = index;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (reader.get(mid) < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (reader.get(start) == target) {
            return start;
        }
        if (reader.get(end) == target) {
            return end;
        }
        return -1;
    }
};

// LeetCode 153 - Find Minimum in Rotated Sorted Array, Binary Search, 20181205
class Solution {
public:
    int findMin(vector<int> &nums) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        int target = nums[end];
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] <= target) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (nums[start] <= target) {
            return nums[start];
        }
        return nums[end];
    }
};

// LeetCode 154 - Find Minimum in Rotated Sorted Array II, Binary Search, 20181205
class Solution {
public:
    int findMin(vector<int> &nums) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        int target = nums[end];
        while (start < end && nums[start] == target) {
            start++;
        }
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] <= target) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (nums[start] <= target) {
            return nums[start];
        }
        return nums[end];
    }
};

// LeetCode 852 - Peak Index in a Mountain Array, Binary Search, 20181205
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        if (A.empty()) {
            return -1;
        }
        
        int start = 0, end = A.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (A[mid] < A[mid + 1]) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (A[start] >= A[end]) {
            return start;
        }
        return end;
    }
};

// LeetCode 74 - Search a 2D Matrix, Binary Search, 20181205
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, 
                      int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int row = matrix.size(), col = matrix[0].size();
        int start = 0, end = row - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (matrix[mid][0] == target) {
                return true;
            }
            if (matrix[mid][0] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
                
        if (matrix[end][0] <= target) {
            row = end;
        } else if (matrix[start][0] <= target) {
            row = start;
        } else {
            return false;
        }
        
        start = 0; 
        end = col - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (matrix[row][mid] == target) {
                return true;
            }
            if (matrix[row][mid] < target) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (matrix[row][start] == target) {
            return true;
        }
        if (matrix[row][end] == target) {
            return true;
        }
        return false;
    }
};

// LeetCode 240 - Search a 2D Matrix II, Binary Search, 20181205
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, 
                      int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        
        int row = matrix.size() - 1, col = 0;
        while (row >= 0 && col < matrix[0].size()) {
            if (matrix[row][col] == target) {
                return true;
            }
            if (matrix[row][col] < target) {
                col++;
            } else {
                row--;
            }
        }
        
        return false;
    }
};

// LeetCode 302 - Smallest Rectangle Enclosing Black Pixels, Binary Search, 20181205
class Solution {
public:
    int minArea(vector<vector<char>>& image, 
                int x, int y) {
        if (image.empty() || image[0].empty()) {
            return 0;
        }
        
        int m = image.size(), n = image[0].size();
        int top = _findTop(image, 0, x);
        int bottom = _findBottom(image, x, m - 1);
        int left = _findLeft(image, 0, y);
        int right = _findRight(image, y, n - 1);
        
        return (bottom - top + 1) * (right - left + 1);
    }
    
private:
    int _findTop(vector<vector<char>> &image, 
                 int start, int end) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (_isEmptyRow(image, mid)) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (!_isEmptyRow(image, start)) {
            return start;
        }
        return end;
    }
    
    int _findBottom(vector<vector<char>> &image, 
                    int start, int end) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (!_isEmptyRow(image, mid)) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (!_isEmptyRow(image, end)) {
            return end;
        }
        return start;
    }
    
    int _findLeft(vector<vector<char>> &image, 
                  int start, int end) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (_isEmptyColumn(image, mid)) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (!_isEmptyColumn(image, start)) {
            return start;
        }
        return end;
    }
    
    int _findRight(vector<vector<char>> &image, 
                   int start, int end) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (!_isEmptyColumn(image, mid)) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (!_isEmptyColumn(image, end)) {
            return end;
        }
        return start;
    }
    
    bool _isEmptyRow(vector<vector<char>> &image, 
                     int row) {
        for (int j = 0; j < image[0].size(); j++) {
            if (image[row][j] == '1') {
                return false;
            }
        }
        return true;
    }
    
    bool _isEmptyColumn(vector<vector<char>> &image, 
                     int col) {
        for (int i = 0; i < image.size(); i++) {
            if (image[i][col] == '1') {
                return false;
            }
        }
        return true;
    }
};

// LeetCode 162 - Find Peak Element, Binary Search, 20181205
class Solution {
public:
    int findPeakElement(vector<int> &nums) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < nums[mid + 1]) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (nums[start] >= nums[end]) {
            return start;
        }
        return end;
    }
};

// LeetCode 33 - Search in Rotated Sorted Array, Binary Search, 20181205
class Solution {
public:
    int search(vector<int> &nums, int target) {
        if (nums.empty()) {
            return -1;
        }
        
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[start] <= nums[mid]) {
                if (nums[start] <= target && 
                            target <= nums[mid]) {
                    end = mid;
                } else {
                    start = mid;
                }
            } else {
                if (nums[mid] <= target && 
                            target <= nums[end]) {
                    start = mid;
                } else {
                    end = mid;
                }
            }
        }
        
        if (nums[start] == target) {
            return start;
        }
        if (nums[end] == target) {
            return end;
        }
        return -1;
    }
};

// LeetCode 81 - Search in Rotated Sorted Array II, Binary Search, 20181205
class Solution {
public:
    bool search(vector<int> &nums, int target) {
        if (nums.empty()) {
            return false;
        }
        
        int start = 0, end = nums.size() - 1;
        if (nums[start] == target) {
            return true;
        }
        while (start < end && nums[start] == nums[end]) {
            start++;
        }
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                return true;
            }
            if (nums[start] <= nums[mid]) {
                if (nums[start] <= target && 
                            target <= nums[mid]) {
                    end = mid;
                } else {
                    start = mid;
                }
            } else {
                if (nums[mid] <= target && 
                            target <= nums[end]) {
                    start = mid;
                } else {
                    end = mid;
                }
            }
        }
        
        if (nums[start] == target) {
            return true;
        }
        if (nums[end] == target) {
            return true;
        }
        return false;
    }
};

// LintCode 140 - Fast Power, Binary Search, 20181205
class Solution {
public:
    int fastPower(int a, int b, int n) {
        if (n == 1) {
            return a % b;
        }
        if (n == 0) {
            return 1 % b;
        }
        
        long long product = fastPower(a, b, n / 2);
        product = (product * product) % b;
        if (n % 2 == 0) {
            return product;
        }
        product = (product * a) % b;
        return product;
    }
};

// LeetCode 50 - Pow(x, n), Binary Search, 20181205
class Solution {
public:
    double myPow(double x, int n) {
        long long m = n;
        if (m < 0) {
            return 1. / _pow(x, -m);
        }
        return _pow(x, m);
    }

private:
    double _pow(double x, long long m) {
        if (m == 0) {
            return 1.;
        }
        
        double v = _pow(x, m / 2);
        if (m % 2 == 0) {
            return v * v;
        }
        return v * v * x;
    }
};

// LintCode 437 - Copy Book, Binary Search, 20181205
class Solution {
public:
    int copyBooks(vector<int> &pages, int k) {
        if (pages.empty() || k <= 0) {
            return 0;
        }
        
        int start = 1, end = INT_MAX;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (_check(pages, mid, k)) {
                end = mid;
            } else {
                start = mid;
            }
        }
        
        if (_check(pages, start, k)) {
            return start;
        }
        return end;
    }
    
private:
    bool _check(vector<int> &pages, int limit, int k) {
        int n = 1, left = limit;
        for (int &page : pages) {
            if (page > limit) {
                return false;
            }
            
            if (page > left) {
                n++;
                left = limit;
            }
            left -= page;
        }
        
        return n <= k;
    }
};

// LintCode 183 - Wood Cut, Binary Search, 20181205
class Solution {
public:
    int woodCut(vector<int> &L, int k) {
        if (L.empty() || k <= 0) {
            return 0;
        }
        
        int start = 1, end = 0;
        for (int i = 0; i < L.size(); i++) {
            end = max(end, L[i]);
        }
        
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (_count(L, mid) >= k) {
                start = mid;
            } else {
                end = mid;
            }
        }
        
        if (_count(L, end) >= k) {
            return end;
        }
        if (_count(L, start) >= k) {
            return start;
        }
        return 0;
    }

private:
    int _count(vector<int> &L, int length) {
        int sum = 0;
        for (int i = 0; i < L.size(); i++) {
            sum += L[i] / length;
        }
        return sum;
    }
};

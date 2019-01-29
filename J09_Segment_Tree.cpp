/******************** Segment Tree ********************/

// LintCode 201 - Segment Tree Build, Segment Tree, 20181225
/**
 * Definition of SegmentTreeNode:
 * class SegmentTreeNode {
 * public:
 *     int start, end;
 *     SegmentTreeNode *left, *right;
 *     SegmentTreeNode(int start, int end) {
 *         this->start = start, this->end = end;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    SegmentTreeNode *build(int start, int end) {
        if (start > end) {
            return nullptr;
        }
        
        SegmentTreeNode *root = new SegmentTreeNode(start, end);
        if (start != end) {
            int mid = start + (end - start) / 2;
            root->left = build(start, mid);
            root->right = build(mid + 1, end);
        }
        
        return root;
    }
};

// LintCode 439 - Segment Tree Build II, Segment Tree, 20181225
/**
 * Definition of SegmentTreeNode:
 * class SegmentTreeNode {
 * public:
 *     int start, end, max;
 *     SegmentTreeNode *left, *right;
 *     SegmentTreeNode(int start, int end, int max) {
 *         this->start = start;
 *         this->end = end;
 *         this->max = max;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    SegmentTreeNode *build(vector<int> &A) {
        if (A.empty()) {
            return nullptr;
        }
        
        return _build(0, A.size() - 1, A);
    }
    
private:
    SegmentTreeNode *_build(int start, int end, vector<int> &A) {
        if (start > end) {
            return nullptr;
        }
        
        SegmentTreeNode *root = new SegmentTreeNode(start, end, A[start]);
        if (start == end) {
            return root;
        }
        
        int mid = start + (end - start) / 2;
        root->left = _build(start, mid, A);
        root->right = _build(mid + 1, end, A);
        root->max = max(root->left->max, root->right->max);
        return root;
    }
};

// LintCode 202 - Segment Tree Query, Segment Tree, 20181225
/**
 * Definition of SegmentTreeNode:
 * class SegmentTreeNode {
 * public:
 *     int start, end, max;
 *     SegmentTreeNode *left, *right;
 *     SegmentTreeNode(int start, int end, int max) {
 *         this->start = start;
 *         this->end = end;
 *         this->max = max;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    int query(SegmentTreeNode *root, int start, int end) {
        if (start > end || root == nullptr) {
            return 0;
        }
        if (start <= root->start && root->end <= end) {
            return root->max;
        }
        
        int result = INT_MIN;
        int mid = root->start + (root->end - root->start) / 2;
        if (start <= mid) {
            result = max(result, query(root->left, start, end));
        }
        if (mid < end) {
            result = max(result, query(root->right, start, end));
        }
        return result;
    }
};

// LintCode 247 - Segment Tree Query II, Segment Tree, 20181225
/**
 * Definition of SegmentTreeNode:
 * class SegmentTreeNode {
 * public:
 *     int start, end, count;
 *     SegmentTreeNode *left, *right;
 *     SegmentTreeNode(int start, int end, int count) {
 *         this->start = start;
 *         this->end = end;
 *         this->count = count;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    int query(SegmentTreeNode *root, int start, int end) {
        if (start > end || root == nullptr) {
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
};

// LintCode 203 - Segment Tree Modify, Segment Tree, 20181225
/**
 * Definition of SegmentTreeNode:
 * class SegmentTreeNode {
 * public:
 *     int start, end, max;
 *     SegmentTreeNode *left, *right;
 *     SegmentTreeNode(int start, int end, int max) {
 *         this->start = start;
 *         this->end = end;
 *         this->max = max;
 *         this->left = this->right = NULL;
 *     }
 * }
 */
class Solution {
public:
    void modify(SegmentTreeNode *root, int index, int value) {
        if (root == nullptr || 
            index < root->start || index > root->end) {
            return;
        }
        if (root->start == index && index == root->end) {
            root->max = value;
            return;
        }
        
        int mid = root->start + (root->end - root->start) / 2;
        if (root->start <= index && index <= mid) {
            modify(root->left, index, value);
        }
        if (mid < index && index <= root->end) {
            modify(root->right, index, value);
        }
        
        root->max = max(root->left->max, root->right->max);
    }
};

// LintCode 206 - Interval Sum, Segment Tree, 20181225
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
class SegTreeNode {
public:
    int start, end;
    long long sum;
    SegTreeNode *left, *right;
    SegTreeNode(int start, int end, long long sum) {
        this->start = start;
        this->end = end;
        this->sum = sum;
        this->left = this->right = nullptr;
    }
};
class SegmentTree {
public:
    SegTreeNode *build(int start, int end, vector<int> &A) {
        if (start > end) {
            return nullptr;
        }
        
        long long val = A[start];
        SegTreeNode *root = new SegTreeNode(start, end, val);
        if (start == end) {
            return root;
        }
        
        int mid = start + (end - start) / 2;
        root->left = build(start, mid, A);
        root->right = build(mid + 1, end, A);
        root->sum = root->left->sum + root->right->sum;
        return root;
    }
    
    long long query(SegTreeNode *root, int start, int end) {
        if (start <= root->start && root->end <= end) {
            return root->sum;
        }
        
        int mid = root->start + (root->end - root->start) / 2;
        long long result = 0;
        if (start <= mid) {
            result += query(root->left, start, end);
        }
        if (mid < end) {
            result += query(root->right, start, end);
        }
        
        return result;
    }
};
class Solution {
public:
    vector<long long> intervalSum(vector<int> &A, 
                                  vector<Interval> &queries) {
        vector<long long> results;
        if (A.empty() || queries.empty()) {
            return results;
        }
        
        SegmentTree *st = new SegmentTree();
        SegTreeNode *root = st->build(0, A.size() - 1, A);
        for (Interval &in : queries) {
            results.push_back(st->query(root, in.start, in.end));
        }
        
        return results;
    }
};

// LeetCode 303 - Range Sum Query - Immutable, Segment Tree, 20181226
class SegmentTreeNode {
public:
    int start, end, sum;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int start, int end, int sum) {
        this->start = start;
        this->end = end;
        this->sum = sum;
        this->left = this->right = nullptr;
    }
};

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

// LintCode 207 - Interval Sum II, Segment Tree, 20181225
class SegTreeNode {
public:
    int start, end;
    long long sum;
    SegTreeNode *left, *right;
    SegTreeNode(int start, int end, long long sum) {
        this->start = start;
        this->end = end;
        this->sum = sum;
        this->left = this->right = nullptr;
    }
};
class Solution {
public:
    Solution(vector<int> &A) {
        root = _build(0, A.size() - 1, A);
    }

    long long query(int start, int end) {
        if (root == nullptr || start > end) {
            return 0;
        }
        return _query(root, start, end);
    }

    void modify(int index, int value) {
        if (root == nullptr || 
            index < root->start || index > root->end) {
            return;
        }
        _modify(root, index, value);
    }
    
private:
    SegTreeNode *root = nullptr;
    
    SegTreeNode *_build(int start, int end, vector<int> &A) {
        if (A.empty() || start > end) {
            return nullptr;
        }
        
        long long sum = A[start];
        SegTreeNode *root = new SegTreeNode(start, end, sum);
        if (start == end) {
            return root;
        }
        
        int mid = start + (end - start) / 2;
        root->left = _build(start, mid, A);
        root->right  = _build(mid + 1, end, A);
        root->sum = root->left->sum + root->right->sum;
        return root;
    }
    
    long long _query(SegTreeNode *root, int start, int end) {
        if (start <= root->start && root->end <= end) {
            return root->sum;
        }
        
        int mid = root->start + (root->end - root->start) / 2;
        long long result = 0;
        if (start <= mid) {
            result += _query(root->left, start, end);
        }
        if (mid < end) {
            result += _query(root->right, start, end);
        }
        
        return result;
    }
    
    void _modify(SegTreeNode *root, int index, int value) {
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

// LeetCode 307 - Range Sum Query - Mutable, Segment Tree, 20181226
class SegmentTreeNode {
public:
    int start, end, sum;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int start, int end, int sum) {
        this->start = start;
        this->end = end;
        this->sum = sum;
        this->left = this->right = nullptr;
    }
};
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

// LintCode 249 - Count of Smaller Number before itself, Segment Tree, 20181226
class SegTreeNode {
public:
    int start, end, count;
    SegTreeNode *left, *right;
    SegTreeNode(int start, int end, int count) {
        this->start = start;
        this->end = end;
        this->count = count;
        this->left = this->right = nullptr;
    }
};
class SegmentTree {
public:
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
};

// LintCode 248 - Count of Smaller Number, Segment Tree, 20181226
class SegTreeNode {
public:
    int start, end, count;
    SegTreeNode *left, *right;
    SegTreeNode(int start, int end, int count) {
        this->start = start;
        this->end = end;
        this->count = count;
        this->left = this->right = nullptr;
    }
};
class SegmentTree {
public:
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
class Solution {
public:
    vector<int> countOfSmallerNumber(vector<int> &A, 
                                     vector<int> &queries) {
        vector<int> results;
        if (queries.empty()) {
            return results;
        }
        
        SegmentTree *st = new SegmentTree();
        SegTreeNode *root = st->build(0, 10000);
        for (int i : A) {
            st->modify(root, i, 1);
        }
        for (int i : queries) {
            int result = st->query(root, 0, i - 1);
            results.push_back(result);
        }
        
        return results;
    }
};

// LintCode 1297 - Count of Smaller Numbers After Self, Segment Tree, 20181226
class SegTreeNode {
public:
    int start, end, count;
    SegTreeNode *left, *right;
    SegTreeNode(int start, int end, int count) {
        this->start = start;
        this->end = end;
        this->count = count;
        this->left = this->right = nullptr;
    }
};
class SegmentTree {
public:
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
class Solution {
public:
    vector<int> countSmaller(vector<int> &nums) {
        vector<int> results;
        if (nums.empty()) {
            return results;
        }
        
        SegmentTree *st = new SegmentTree();
        SegTreeNode *root = st->build(-10000, 10000);
        for (int i = nums.size() - 1; i >= 0; i--) {
            int result = st->query(root, -10000, nums[i] - 1);
            st->modify(root, nums[i], 1);
            results.push_back(result);
        }
        
        reverse(results.begin(), results.end());
        return results;
    }
};

// LeetCode 315 - Count of Smaller Numbers After Self, Segment Tree, 20181226
class SegmentTreeNode {
public:
    int start, end, count;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int start, int end, int count) {
        this->start = start;
        this->end = end;
        this->count = count;
        this->left = this->right = nullptr;
    }
};
class SegmentTree {
public:
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
};

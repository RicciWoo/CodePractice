#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Merge k Sorted List, use Heap
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class myComparator {
public:
    int operator() (const ListNode *n1, const ListNode *n2) {
        return n1->val > n2->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return NULL;
        priority_queue<ListNode *, vector<ListNode *>, 
                       myComparator> minHeap;
        for (int i = 0; i < lists.size(); i++)
            if (lists[i] != NULL)
                minHeap.push(lists[i]);
        ListNode *dummy = new ListNode(-1);
        ListNode *curr = dummy;
        while (!minHeap.empty()) {
            curr->next = minHeap.top();
            minHeap.pop();
            curr = curr->next;
            if (curr->next != NULL)
                minHeap.push(curr->next);
        }
        return dummy->next;
    }
};

int main(int argc, char **argv) {
    ListNode *l1 = new ListNode(1);
    ListNode *node = l1;
    node->next = new ListNode(4);
    node = node->next;
    node->next = new ListNode(5);

    ListNode *l2 = new ListNode(1);
    node = l2;
    node->next = new ListNode(3);
    node = node->next;
    node->next = new ListNode(4);

    ListNode *l3 = new ListNode(2);
    node = l3;
    node->next = new ListNode(6);

    vector<ListNode *> lists{l1, l2, l3};

    cout << "Input:" << endl;
    cout << "[" << endl;
    for (ListNode *list : lists) {
        if (list) {
            cout << "   " << list->val;
            list = list->next;
        }
        while (list) {
            cout << "->" << list->val;
            list = list->next;
        }
        cout << "," << endl;
    }
    cout << "]" << endl;

    ListNode *result;
    Solution *solution = new Solution;
    result = solution->mergeKLists(lists);

    cout << "Output: ";
    if (result) {
        cout << result->val;
        result = result->next;
    }
    while (result) {
        cout << "->" << result->val;
        result = result->next;
    }
    cout << endl;
}

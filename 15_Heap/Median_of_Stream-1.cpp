#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Find Median in Data Stream-1, use Heap
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

int main(int argc, char **argv) {
    MedianFinder *medianFinder = new MedianFinder;
    medianFinder->addNum(1);
    cout << "add number: 1" << endl;
    medianFinder->addNum(2);
    cout << "add number: 2" << endl;
    double result = medianFinder->findMedian();
    cout << "median so far: " << result << endl;
    medianFinder->addNum(3);
    cout << "add number: 3" << endl;
    result = medianFinder->findMedian();
    cout << "median so far: " << result << endl;
}

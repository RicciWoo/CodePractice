#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Find Median in Data Stream-2, use Heap
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

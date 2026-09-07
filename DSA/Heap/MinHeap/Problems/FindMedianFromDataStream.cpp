class MedianFinder {
public:

    // LEFT = smaller half of numbers
    // Max Heap because we need the LARGEST number of the smaller half.
    priority_queue<int> leftMaxHeap;

    // RIGHT = larger half of numbers
    // Min Heap because we need the SMALLEST number of the larger half.
    priority_queue<int, vector<int>, greater<int>> rightMinHeap;


    MedianFinder() {
        // Nothing to initialize manually.
        // Both heaps are automatically created empty.
    }
    

    void addNum(int num) {

        // First number always goes into the left heap.
        if (leftMaxHeap.empty()) {
            leftMaxHeap.push(num);
            return;
        }


        // leftMaxHeap.top() acts like the boundary between
        // the smaller half and larger half.
        //
        // If num is smaller than the largest element of left half,
        // it belongs to the LEFT heap.
        if (num < leftMaxHeap.top()) {
            leftMaxHeap.push(num);
        }
        else {
            // Otherwise it belongs to the larger half.
            rightMinHeap.push(num);
        }


        // After insertion, one heap may become too large.
        // Restore the size property.
        BalanceTwoHeaps();
    }
    

    double findMedian() {

        double ans;


        // ODD number of elements:
        //
        // Left heap is allowed to contain ONE extra element.
        // That extra element (leftMaxHeap.top()) is the median.
        //
        // Example:
        // LEFT        RIGHT
        // 1 2 3       4 5
        //     ^
        //   median
        if (leftMaxHeap.size() > rightMinHeap.size()) {

            ans = leftMaxHeap.top();
        }


        // EVEN number of elements:
        //
        // Both heaps have equal size.
        //
        // The two middle values are:
        // 1. Largest of smaller half  -> leftMaxHeap.top()
        // 2. Smallest of larger half -> rightMinHeap.top()
        //
        // Median = average of these two.
        //
        // Example:
        // LEFT       RIGHT
        // 1 2    |    3 4
        //   ^         ^
        //
        // median = (2 + 3) / 2.0
        if (leftMaxHeap.size() == rightMinHeap.size()) {

            int leftMiddle = leftMaxHeap.top();
            int rightMiddle = rightMinHeap.top();

            ans = ((double)leftMiddle + rightMiddle) / 2.0;
        }


        return ans;
    }


    void BalanceTwoHeaps() {

        // RULE:
        //
        // leftMaxHeap.size() == rightMinHeap.size()
        //
        // OR
        //
        // leftMaxHeap.size() == rightMinHeap.size() + 1
        //
        // Left can have AT MOST one extra element.


        // If RIGHT becomes bigger than LEFT,
        // move the smallest element of RIGHT to LEFT.
        if (rightMinHeap.size() > leftMaxHeap.size()) {

            leftMaxHeap.push(rightMinHeap.top());
            rightMinHeap.pop();

            return;
        }


        // If LEFT has more than one extra element,
        // move the largest element of LEFT to RIGHT.
        if (leftMaxHeap.size() > rightMinHeap.size() + 1) {

            rightMinHeap.push(leftMaxHeap.top());
            leftMaxHeap.pop();

            return;
        }
    }
};
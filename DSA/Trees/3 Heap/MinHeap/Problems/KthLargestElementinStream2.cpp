// Constructor: O(n log k)
// add():       O(log k)
// Space:       O(k)


class KthLargest {
public:
    // Min heap that stores only the K largest elements seen so far.
    // The smallest among these K elements is the Kth largest.
    priority_queue<int, vector<int>, greater<int>> minHeap;

    int kth;

    KthLargest(int k, vector<int>& nums) {
        kth = k;

        // Process the initial stream.
        for (int num : nums) {

            minHeap.push(num);

            // Keep only the K largest elements.
            // If size exceeds K, remove the smallest element.
            if (minHeap.size() > kth) {
                minHeap.pop();
            }
        }
    }

    int add(int val) {

        // Add the new value to the stream.
        minHeap.push(val);

        // Keep only the K largest values seen so far.
        // Min heap removes the smallest unwanted value.
        if (minHeap.size() > kth) {
            minHeap.pop();
        }

        // Heap contains the K largest values.
        // Smallest among them = Kth largest.
        return minHeap.top();
    }
};
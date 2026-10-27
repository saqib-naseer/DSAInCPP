#include <iostream>
// ============================================================
// Approach 1: Min Heap
// ============================================================
// Idea:
// Put all elements into a min heap.
// Remove the smallest element k-1 times.
// The heap top is then the kth smallest element.
//
// Time Complexity:  O(n log n + k log n)
// Space Complexity: O(n)

int kthSmallestUsingMinHeap(vector<int>& arr, int k) {

    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Store all elements in the min heap
    for(int num : arr) {
        minHeap.push(num);
    }

    // Remove the first k-1 smallest elements
    while(k > 1) {
        minHeap.pop();
        k--;
    }

    // kth smallest is now at the top
    return minHeap.top();
}


// ============================================================
// Approach 2: Max Heap Containing All Elements
// ============================================================
// Idea:
// Put all elements into a max heap.
// Keep removing the largest elements until exactly k remain.
//
// Why does this work?
// After removing the n-k largest elements, the remaining heap
// contains the k smallest elements of the array.
// The largest among those k elements is the kth smallest.
//
// Time Complexity:  O(n log n)
// Space Complexity: O(n)

int kthSmallestUsingFullMaxHeap(vector<int>& arr, int k) {

    priority_queue<int> maxHeap;

    // Store all elements in the max heap
    for(int num : arr) {
        maxHeap.push(num);
    }

    // Remove larger elements until only k elements remain
    while(maxHeap.size() > k) {
        maxHeap.pop();
    }

    // Largest among the k smallest = kth smallest
    return maxHeap.top();
}

// ============================================================
// Approach 3: Sorting
// ============================================================
// Idea:
// Sort the array in ascending order.
// Since indexing starts from 0, the kth smallest element
// is stored at index k-1.
//
// Time Complexity:  O(n log n)
// Space Complexity: depends on sorting implementation

int kthSmallestUsingSorting(vector<int>& arr, int k) {

    sort(arr.begin(), arr.end());

    return arr[k - 1];
}

// ============================================================
// Approach 4: Max Heap of Size K
// ============================================================
// Idea:
// Maintain only the k smallest elements seen so far.
//
// The max heap contains at most k elements.
// Its top represents the LARGEST among those k smallest elements.
//
// For every remaining array element:
// - If it is smaller than maxHeap.top(),
//   it deserves to be among our k smallest.
// - Remove the current largest and insert the new smaller value.
//
// At the end:
// largest among k smallest = kth smallest.
//
// Time Complexity:  O(n log k)
// Space Complexity: O(k)

int kthSmallestUsingMaxHeap(vector<int>& arr, int k) {

    priority_queue<int> maxHeap;

    // Start with the first k elements
    for(int i = 0; i < k; i++) {
        maxHeap.push(arr[i]);
    }

    // Check remaining elements
    for(int i = k; i < arr.size(); i++) {

        // Found a value smaller than the largest
        // element currently among our k smallest
        if(arr[i] < maxHeap.top()) {

            maxHeap.pop();
            maxHeap.push(arr[i]);
        }
    }

    // Largest among the k smallest = kth smallest
    return maxHeap.top();
}

int main() {

  
}

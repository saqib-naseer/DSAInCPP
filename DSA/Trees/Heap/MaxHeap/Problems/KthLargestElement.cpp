#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


// ============================================================
// Approach 1: Sorting
// ============================================================
// Idea:
// Sort the array in ascending order.
// The kth largest element will be at index n - k.
//
// Time:  O(n log n)
// Space: depends on sorting implementation

int findKthLargestUsingSorting(vector<int>& nums, int k) {

    sort(nums.begin(), nums.end());

    int n = nums.size();

    return nums[n - k];
}


// ============================================================
// Approach 2: Full Min Heap
// ============================================================
// Idea:
// Put all elements into a min heap.
// Remove the smallest elements until only k elements remain.
//
// Those remaining k elements are the k largest elements.
// The smallest among them = kth largest.
//
// Time:  O(n log n)
// Space: O(n)

int findKthLargestUsingFullMinHeap(vector<int>& nums, int k) {

    priority_queue<int, vector<int>, greater<int>> minHeap;

    for(int num : nums) {
        minHeap.push(num);
    }

    // Remove smaller elements until only k largest remain
    while(minHeap.size() > k) {
        minHeap.pop();
    }

    // Smallest among the k largest = kth largest
    return minHeap.top();
}


// ============================================================
// Approach 3: Min Heap of Size K
// ============================================================
// Idea:
// Maintain only the k largest elements seen so far.
//
// The min heap gives quick access to the smallest element
// among our current k largest.
//
// If a new number is greater than heap.top(),
// replace the top with the new number.
//
// At the end:
// smallest among k largest = kth largest.
//
// Time:  O(n log k)
// Space: O(k)

int findKthLargestUsingMinHeapOfK(vector<int>& nums, int k) {

    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Start with first k elements
    for(int i = 0; i < k; i++) {
        minHeap.push(nums[i]);
    }

    // Process the remaining elements
    for(int i = k; i < nums.size(); i++) {

        if(nums[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(nums[i]);
        }
    }

    // Smallest among the k largest = kth largest
    return minHeap.top();
}


// ============================================================
// Approach 4: Full Max Heap
// ============================================================
// Idea:
// Put all elements into a max heap.
// Remove the largest element k-1 times.
// The next element on top is the kth largest.
//
// Time:  O(n log n + k log n)
// Space: O(n)

int findKthLargestUsingMaxHeap(vector<int>& nums, int k) {

    priority_queue<int> maxHeap;

    for(int num : nums) {
        maxHeap.push(num);
    }

    // Remove first k-1 largest elements
    while(k > 1) {
        maxHeap.pop();
        k--;
    }

    return maxHeap.top();
}


int main() {

    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;

    cout << findKthLargestUsingMinHeapOfK(nums, k);

    return 0;
}
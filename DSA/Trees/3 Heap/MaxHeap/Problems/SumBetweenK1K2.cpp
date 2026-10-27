#include <iostream>

// ============================================================
// Sum Between K1th and K2th Smallest
// ============================================================


// ------------------------------------------------------------
// Approach 1: Sorting
// ------------------------------------------------------------
// After sorting, the Kth smallest element is at index K-1.
//
// Example:
// arr = [20, 8, 22, 4, 12, 10, 14], k1 = 3, k2 = 6
//
// Sorted:
// [4, 8, 10, 12, 14, 20]
//        ↑           ↑
//      3rd          6th
//
// We must EXCLUDE both K1th and K2th smallest.
// Therefore sum indices [k1 ... k2-2].
// Here: 12 + 14 = 26.
//
// Time:  O(n log n)
// Space: O(1) auxiliary (ignoring sort implementation)

int sumBetweenK1K2(vector<int>& arr, int k1, int k2) {

    sort(arr.begin(), arr.end());

    int sum = 0;

    // k1 is already the index AFTER the k1th smallest
    // because array indexing is 0-based.
    // Stop before index k2-1 (the k2th smallest).
    for (int i = k1; i < k2 - 1; i++) {
        sum += arr[i];
    }

    return sum;
}


// ------------------------------------------------------------
// Approach 2: Bounded Max Heaps
// ------------------------------------------------------------
// Key idea:
//
// MAX heap of size K keeps the K SMALLEST elements.
// Whenever size > K, pop() removes the largest candidate.
//
// We need elements strictly BETWEEN K1th and K2th:
//
// sum(first K2-1 smallest)
//          -
// sum(first K1 smallest)
//
// Example:
// Sorted: [4, 8, 10, 12, 14, 20]
//
// first K2-1 = [4, 8, 10, 12, 14]
// first K1   = [4, 8, 10]
//
// Difference = 12 + 14 = 26
//
// Time:  O(n log k2)
// Space: O(k1 + k2)

int sumBetweenK1K2(vector<int>& arr, int k1, int k2) {

    priority_queue<int> firstK1Smallest;
    priority_queue<int> firstK2Minus1Smallest;

    // Keep only the K1 smallest elements.
    for (int num : arr) {

        firstK1Smallest.push(num);

        if (firstK1Smallest.size() > k1) {
            firstK1Smallest.pop();
        }
    }

    // Keep only the first K2-1 smallest elements.
    // We use K2-1 because K2th itself must be excluded.
    for (int num : arr) {

        firstK2Minus1Smallest.push(num);

        if (firstK2Minus1Smallest.size() > k2 - 1) {
            firstK2Minus1Smallest.pop();
        }
    }

    int sumK1 = 0;

    while (!firstK1Smallest.empty()) {
        sumK1 += firstK1Smallest.top();
        firstK1Smallest.pop();
    }

    int sumK2Minus1 = 0;

    while (!firstK2Minus1Smallest.empty()) {
        sumK2Minus1 += firstK2Minus1Smallest.top();
        firstK2Minus1Smallest.pop();
    }

    return sumK2Minus1 - sumK1;
}
int main() {

}

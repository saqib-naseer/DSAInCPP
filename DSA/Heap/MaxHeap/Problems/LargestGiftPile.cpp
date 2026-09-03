/*
LeetCode 2558 — Take Gifts From the Richest Pile

Pattern:
Repeatedly need the LARGEST element
→ MAX HEAP

Algorithm:

1. Put every gift pile into a max heap.

2. Repeat k times:
      largest = heap.top()
      pop it

      remaining = floor(sqrt(largest))

      push remaining back

3. Add all values remaining in the heap.

Why Max Heap?
Every operation specifically requires us to choose
the pile containing the maximum number of gifts.

Time:
Building with pushes → O(n log n)
k operations        → O(k log n)
Final sum           → O(n log n) if popping

Overall → O((n + k) log n)

Space → O(n)
*/

class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {

        // Max heap: always gives us the largest gift pile
        priority_queue<int> maxHeap;

        // Add all gift piles to the max heap
        for(int gift : gifts) {
            maxHeap.push(gift);
        }

        // Perform the operation exactly k times
        while(k > 0) {

            // Pick the largest gift pile
            int largestGift = maxHeap.top();
            maxHeap.pop();

            // After taking gifts, floor(sqrt(largestGift))
            // gifts remain in that pile
            int remainingGifts = sqrt(largestGift);

            // Put the updated pile back into the heap
            maxHeap.push(remainingGifts);

            k--;
        }

        // Sum all gift piles remaining after k operations
        long long totalRemainingGifts = 0;

        while(!maxHeap.empty()) {
            totalRemainingGifts += maxHeap.top();
            maxHeap.pop();
        }

        return totalRemainingGifts;
    }
};
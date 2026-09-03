/*Last Stone Weight — Max Heap

Pattern:
Repeatedly need the TWO LARGEST elements
→ use a MAX HEAP

Algorithm:
1. Put all stones into a max heap.
2. While heap has more than one stone:
   - Pop the heaviest stone.
   - Pop the second heaviest stone.
   - Smash them.
   - remainingWeight = heaviest - secondHeaviest
   - If remainingWeight > 0, push it back.
3. If heap is empty → return 0.
4. Otherwise → return heap.top().

Why max heap?
We repeatedly need the two largest stones.

Time:  O(n log n)
Space: O(n)
*/

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {

        // Max heap keeps the heaviest stone at the top
        priority_queue<int> maxHeap;

        // Add all stones to the max heap
        for(int stone : stones) {
            maxHeap.push(stone);
        }

        // Keep smashing the two heaviest stones
        // until at most one stone remains
        while(maxHeap.size() > 1) {

            int heaviest = maxHeap.top();
            maxHeap.pop();

            int secondHeaviest = maxHeap.top();
            maxHeap.pop();

            // Since heaviest >= secondHeaviest,
            // the remaining stone has their weight difference
            int remainingWeight = heaviest - secondHeaviest;

            // Equal stones destroy each other, so only push
            // the remainder if it is greater than 0
            if(remainingWeight > 0) {
                maxHeap.push(remainingWeight);
            }
        }

        // No stones left → 0
        // Otherwise the only remaining stone is at the top
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {

        // Heap element:
        // {value, {row, col}}
        //
        // We keep ONE current candidate from every list.
        using Element = pair<int, pair<int, int>>;

        priority_queue<
            Element,
            vector<Element>,
            greater<Element>
        > minHeap;


        // currentMax = maximum among the elements
        // currently represented in the heap.
        int currentMax = INT_MIN;


        // -------------------------------------------------------
        // STEP 1: Put the first element of every list in min heap
        // -------------------------------------------------------
        //
        // Since we have one element from EVERY list,
        // these elements already form a valid range.
        //
        // Heap top gives current MIN.
        // currentMax gives current MAX.
        //
        // Current range = [minHeap.top().first, currentMax]
        for (int row = 0; row < nums.size(); row++) {

            minHeap.push({
                nums[row][0],
                {row, 0}
            });

            currentMax = max(currentMax, nums[row][0]);
        }


        // Initial valid range.
        int bestStart = minHeap.top().first;
        int bestEnd = currentMax;


        // -------------------------------------------------------
        // STEP 2: Keep improving the range
        // -------------------------------------------------------
        while (true) {

            // Get the current minimum element.
            Element current = minHeap.top();
            minHeap.pop();

            int currentMin = current.first;
            int row = current.second.first;
            int col = current.second.second;


            // ---------------------------------------------------
            // IMPORTANT STOPPING CONDITION
            // ---------------------------------------------------
            //
            // We popped the representative of this row.
            //
            // If this row has no next element, we cannot replace it.
            // That means we can no longer maintain one candidate
            // from EVERY list.
            //
            // Therefore no more valid ranges can be created.
            if (col + 1 == nums[row].size()) {
                break;
            }


            // Move forward ONLY in the list that supplied
            // the current minimum.
            int nextValue = nums[row][col + 1];

            minHeap.push({
                nextValue,
                {row, col + 1}
            });


            // The new value may increase our current maximum.
            //
            // currentMax never needs to decrease because every
            // individual list is sorted and we only move forward.
            currentMax = max(currentMax, nextValue);


            // Heap again contains ONE element from EVERY list.
            //
            // Therefore:
            // heap top    = current minimum
            // currentMax  = current maximum
            //
            // Together they form another valid range.
            currentMin = minHeap.top().first;


            // Update answer if:
            // 1. New range is smaller
            //
            // OR
            //
            // 2. Same size, but new range starts smaller.
            int currentWidth = currentMax - currentMin;
            int bestWidth = bestEnd - bestStart;

            if (currentWidth < bestWidth ||
                (currentWidth == bestWidth && currentMin < bestStart)) {

                bestStart = currentMin;
                bestEnd = currentMax;
            }
        }


        return {bestStart, bestEnd};
    }
};
class Solution {
public:
    // ============================================================
    // APPROACH: BINARY SEARCH ON VALUE / ANSWER
    // Remaining Approaches in Min Heap Problems/KthSmallestElementInMatrixLC378.cpp
    // ============================================================
    // Best approach here when exploiting sorted matrix structure.
    //
    // IMPORTANT:
    // We are NOT binary searching matrix indexes.
    // We binary search the RANGE OF POSSIBLE ANSWER VALUES.
    //
    // low  = smallest matrix value
    // high = largest matrix value
    //
    // For every mid ask:
    //
    //     "How many matrix elements are <= mid?"
    //
    // We are looking for:
    //
    //     smallest VALUE where count >= k
    //
    // Think:
    //
    // NO  NO  NO  NO | YES YES YES YES
    //                  ^
    //               answer
    //
    // mid does NOT need to actually exist in the matrix.
    //
    // Time:
    // Each row uses upper_bound -> O(log n)
    // n rows                 -> O(n log n)
    // Value binary search    -> O(log(valueRange))
    //
    // Total: O(n log n * log(valueRange))
    // Space: O(1)
    // ============================================================
    int kthSmallestApproach5(vector<vector<int>>& matrix, int k) {

        int n = matrix.size();

        // Possible answer range
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];

        while (low < high) {

            // Middle VALUE, not middle matrix index
            int mid = low + (high - low) / 2;

            int count = 0;

            // Count how many elements in the whole matrix are <= mid
            for (int row = 0; row < n; row++) {

                // upper_bound(mid):
                // returns iterator to first element > mid.
                //
                // Therefore:
                //
                // upper_bound(...) - begin()
                //
                // = number of elements <= mid in this row.
                //
                // Example:
                // [10, 11, 13], mid = 12
                //
                // upper_bound points to 13 (index 2)
                // => 2 elements <= 12.
                int elementsLessOrEqual =
                    upper_bound(
                        matrix[row].begin(),
                        matrix[row].end(),
                        mid
                    ) - matrix[row].begin();

                count += elementsLessOrEqual;
            }


            if (count < k) {

                // NOT ENOUGH elements <= mid.
                //
                // We have not reached the kth position.
                // Therefore mid is DEFINITELY too small.
                //
                // mid cannot be the answer, so discard it.
                low = mid + 1;
            }
            else {

                // ENOUGH elements <= mid.
                //
                // mid is big enough, BUT maybe a smaller
                // value is also big enough.
                //
                // Keep mid because it COULD be the answer.
                //
                // This is why:
                // high = mid
                //
                // NOT:
                // high = mid - 1
                high = mid;
            }
        }

        // low == high
        //
        // We found the SMALLEST value for which
        // at least k elements are <= that value.
        //
        // Therefore it is the kth smallest element.
        return low;
    }
};
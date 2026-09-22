class Solution {
public:

    // ============================================================
    // APPROACH 1: BRUTE FORCE - Flatten + Sort
    // ============================================================
    // Idea:
    // 1. Put every matrix element into a 1D array.
    // 2. Sort the array.
    // 3. kth smallest is at index k - 1.
    //
    // Does NOT take advantage of rows/columns being sorted.
    //
    // Time:  O(n^2 log(n^2))
    // Space: O(n^2)
    // ============================================================
    int kthSmallestApproach1(vector<vector<int>>& matrix, int k) {

        int n = matrix.size();
        vector<int> values;

        // Flatten matrix into a single array
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                values.push_back(matrix[row][col]);
            }
        }

        sort(values.begin(), values.end());

        return values[k - 1];
    }


    // ============================================================
    // APPROACH 2: MIN HEAP - Put All Elements in Heap
    // ============================================================
    // Idea:
    // 1. Push every matrix element into a min heap.
    // 2. Pop k - 1 smallest elements.
    // 3. Heap top is now the kth smallest.
    //
    // Still does NOT take advantage of sorted rows/columns.
    //
    // Time:  O(n^2 log(n^2)) + O(k log(n^2))
    // Space: O(n^2)
    // ============================================================
    int kthSmallestApproach2(vector<vector<int>>& matrix, int k) {

        int n = matrix.size();

        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Push all elements into min heap
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                minHeap.push(matrix[row][col]);
            }
        }

        // Remove first k - 1 smallest elements
        while (k > 1) {
            minHeap.pop();
            k--;
        }

        return minHeap.top();
    }


    // ============================================================
    // APPROACH 3: MIN HEAP - K-WAY MERGE OF SORTED ROWS
    // ============================================================
    // Idea:
    // Every row is already sorted.
    //
    // Instead of pushing ALL n^2 elements:
    // 1. Push only the first element of every row.
    // 2. Pop the smallest element.
    // 3. Push the NEXT element from the SAME row.
    // 4. kth pop = kth smallest.
    //
    // Heap stores:
    // { value, { row, col } }
    //
    // Example:
    //
    // 1   5   9
    // 10  11  13
    // 12  13  15
    //
    // Initially push: 1, 10, 12
    //
    // Pop 1  -> push 5  (next from row 0)
    // Pop 5  -> push 9
    // Pop 9  -> row 0 finished
    // ...
    //
    // IMPORTANT:
    // No visited[][] is needed because every cell can only be
    // inserted from the previous column of its own row.
    //
    // Time:  O(n log n + k log n)
    // Space: O(n)
    // ============================================================
    int kthSmallestApproach3(vector<vector<int>>& matrix, int k) {

        int n = matrix.size();

        // Heap element = {value, {row, col}}
        using Cell = pair<int, pair<int, int>>;

        priority_queue<Cell, vector<Cell>, greater<Cell>> minHeap;

        // Put the first element of every sorted row into heap
        for (int row = 0; row < n; row++) {
            minHeap.push({matrix[row][0], {row, 0}});
        }

        int answer = -1;

        while (k--) {

            Cell current = minHeap.top();
            minHeap.pop();

            answer = current.first;

            int row = current.second.first;
            int col = current.second.second;

            // Since the row is sorted, after removing matrix[row][col],
            // the next candidate from this row is matrix[row][col + 1].
            if (col + 1 < n) {
                minHeap.push({
                    matrix[row][col + 1],
                    {row, col + 1}
                });
            }
        }

        // kth element popped from min heap
        return answer;
    }


    // ============================================================
    // APPROACH 4: MIN HEAP - EXPLORE RIGHT + DOWN
    // ============================================================
    // Idea:
    // Since rows AND columns are sorted:
    //
    // Start from top-left matrix[0][0] (smallest element).
    //
    // Whenever a cell (row, col) is popped:
    //
    //          current
    //          /     \
    //       RIGHT    DOWN
    //    (r,c+1)   (r+1,c)
    //
    // Add its right and down neighbors as future candidates.
    //
    // WHY visited[][] IS REQUIRED:
    //
    // A cell can be reached through TWO different paths.
    //
    //              (0,1)
    //                |
    //               DOWN
    //                v
    //              (1,1)
    //                ^
    //               RIGHT
    //                |
    //              (1,0)
    //
    // Therefore (1,1) could accidentally be inserted twice.
    //
    // IMPORTANT:
    // visited tracks COORDINATES, not values.
    //
    // Two different cells may legitimately contain the same value:
    // matrix[1][2] = 13
    // matrix[2][1] = 13
    //
    // Both must still be counted.
    //
    // Mark visited WHEN PUSHING, not when popping.
    //
    // Time:  roughly O(k log k)
    // Space: O(n^2) because of visited matrix
    // ============================================================
    int kthSmallestApproach4(vector<vector<int>>& matrix, int k) {

        int n = matrix.size();

        using Cell = pair<int, pair<int, int>>;

        priority_queue<Cell, vector<Cell>, greater<Cell>> minHeap;

        vector<vector<bool>> visited(
            n,
            vector<bool>(n, false)
        );

        // Start from top-left: smallest matrix element
        minHeap.push({matrix[0][0], {0, 0}});
        visited[0][0] = true;

        int answer = -1;

        while (k--) {

            Cell current = minHeap.top();
            minHeap.pop();

            answer = current.first;

            int row = current.second.first;
            int col = current.second.second;


            // ---------- RIGHT NEIGHBOR ----------
            if (col + 1 < n && !visited[row][col + 1]) {

                minHeap.push({
                    matrix[row][col + 1],
                    {row, col + 1}
                });

                // Mark when inserted so another path
                // cannot insert the same CELL again.
                visited[row][col + 1] = true;
            }


            // ---------- DOWN NEIGHBOR ----------
            if (row + 1 < n && !visited[row + 1][col]) {

                minHeap.push({
                    matrix[row + 1][col],
                    {row + 1, col}
                });

                visited[row + 1][col] = true;
            }
        }

        // kth popped element = kth smallest
        return answer;
    }


    // ============================================================
    // APPROACH 5: BINARY SEARCH ON VALUE / ANSWER
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
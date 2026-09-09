class Solution {
public:

    // ============================================================
    // APPROACH 1: BRUTE FORCE - Flatten + STL Sort
    // ============================================================
    //
    // Idea:
    // 1. Copy every element from all rows into one array.
    // 2. Sort the complete array using STL sort().
    //
    // We are NOT taking advantage of the fact that every
    // individual row is already sorted.
    //
    // Let N = total number of elements in all rows.
    //
    // Time:  O(N log N)
    // Space: O(N) for answer array
    // ============================================================
    vector<int> mergeArraysApproach1(vector<vector<int>>& mat) {

        vector<int> arr;

        // Flatten the complete matrix into one array.
        for (int row = 0; row < mat.size(); row++) {

            for (int col = 0; col < mat[row].size(); col++) {
                arr.push_back(mat[row][col]);
            }
        }

        // Sort all N elements.
        sort(arr.begin(), arr.end());

        return arr;
    }


    // ============================================================
    // APPROACH 2: PUSH ALL ELEMENTS INTO MIN HEAP
    // ============================================================
    //
    // Idea:
    // 1. Push EVERY element into a min heap.
    // 2. Repeatedly pop the smallest element.
    // 3. Append each popped element to answer.
    //
    // Since minHeap.top() always gives the smallest remaining
    // element, the output automatically comes out sorted.
    //
    // Again, this does NOT take advantage of each row being sorted.
    //
    // Heap may contain up to N elements.
    //
    // Time:  O(N log N)
    // Space: O(N)
    // ============================================================
    vector<int> mergeArraysApproach2(vector<vector<int>>& mat) {

        priority_queue<
            int,
            vector<int>,
            greater<int>
        > minHeap;

        // Push every matrix element into min heap.
        for (int row = 0; row < mat.size(); row++) {

            for (int col = 0; col < mat[row].size(); col++) {
                minHeap.push(mat[row][col]);
            }
        }

        vector<int> answer;

        // Smallest remaining element is always at heap top.
        while (!minHeap.empty()) {

            answer.push_back(minHeap.top());
            minHeap.pop();
        }

        return answer;
    }


    // ============================================================
    // APPROACH 3: K-WAY MERGE USING MIN HEAP
    // ============================================================
    //
    // IMPORTANT:
    // Every row is already SORTED.
    //
    // Instead of putting ALL N elements into the heap,
    // put only ONE candidate from each row.
    //
    // Initially:
    //     push first element of every row.
    //
    // Whenever an element is popped:
    //     push the NEXT element from the SAME row.
    //
    //
    // Example:
    //
    // Row 0:  1   4   7
    // Row 1:  2   5   8
    // Row 2:  3   6   9
    //
    // Initially heap contains:
    //
    //      1  <- row 0
    //      2  <- row 1
    //      3  <- row 2
    //
    // Pop 1
    //      ↓
    // Push 4 because 4 is the next element from row 0.
    //
    // Heap now contains:
    //      2, 3, 4
    //
    // Pop 2
    //      ↓
    // Push 5 from row 1.
    //
    // Continue until heap becomes empty.
    //
    //
    // WHY STORE {value, row, col}?
    //
    // After popping a value, we need to know WHERE it came from
    // so that we can push:
    //
    //      mat[row][col + 1]
    //
    //
    // Heap size stays around number of rows (K),
    // rather than containing all N elements.
    //
    // Time:  O(N log K)
    // Space: O(K) heap + O(N) answer
    //
    // This is the classic K-WAY MERGE pattern.
    // ============================================================
    vector<int> mergeArraysApproach3(vector<vector<int>>& mat) {

        // Heap item:
        // { value, { row, col } }
        using Element = pair<int, pair<int, int>>;

        priority_queue<
            Element,
            vector<Element>,
            greater<Element>
        > minHeap;

        // Push ONLY the first element from each sorted row.
        for (int row = 0; row < mat.size(); row++) {

            // Safety in case an input row is empty.
            if (!mat[row].empty()) {
                minHeap.push({
                    mat[row][0],
                    {row, 0}
                });
            }
        }

        vector<int> answer;

        while (!minHeap.empty()) {

            // Get the smallest available element.
            Element current = minHeap.top();
            minHeap.pop();

            int value = current.first;
            int row = current.second.first;
            int col = current.second.second;

            answer.push_back(value);


            // Since this row is sorted, the NEXT possible
            // candidate from this same row is col + 1.
            if (col + 1 < mat[row].size()) {

                minHeap.push({
                    mat[row][col + 1],
                    {row, col + 1}
                });
            }
        }

        return answer;
    }


    // ============================================================
    // APPROACH 4: FLATTEN + MANUAL MERGE SORT
    // ============================================================
    //
    // Idea:
    // 1. Put all elements into one array.
    // 2. Apply Merge Sort to that array.
    //
    // Merge Sort follows:
    //
    //              Complete Array
    //                /        \
    //             Left        Right
    //             / \          / \
    //            ...          ...
    //
    // Keep dividing until each portion contains ONE element.
    //
    // Then merge the sorted portions back together.
    //
    // NOTE:
    // This is useful for practicing Merge Sort, but just like
    // Approach 1, it does NOT exploit the fact that the original
    // rows are already sorted.
    //
    // Time:  O(N log N)
    // Space: O(N)
    // ============================================================


    // ------------------------------------------------------------
    // MERGE TWO SORTED PORTIONS
    // ------------------------------------------------------------
    //
    // At this point we assume:
    //
    // arr[start ... mid]     is sorted
    // arr[mid+1 ... end]     is sorted
    //
    // p1 points to the first portion.
    // p2 points to the second portion.
    //
    // Repeatedly take the smaller front element and put it
    // into temp.
    // ------------------------------------------------------------
    void merge(
        vector<int>& arr,
        int start,
        int end,
        int mid
    ) {

        vector<int> temp;

        int p1 = start;      // Pointer for LEFT sorted portion
        int p2 = mid + 1;    // Pointer for RIGHT sorted portion


        // Compare the front elements of both sorted portions.
        //
        // Exactly ONE element is selected on each iteration.
        while (p1 <= mid && p2 <= end) {

            if (arr[p1] <= arr[p2]) {

                // Left element is smaller/equal.
                temp.push_back(arr[p1]);
                p1++;
            }
            else {

                // Right element is smaller.
                temp.push_back(arr[p2]);
                p2++;
            }
        }


        // If RIGHT portion finished first,
        // copy remaining LEFT elements.
        while (p1 <= mid) {

            temp.push_back(arr[p1]);
            p1++;
        }


        // If LEFT portion finished first,
        // copy remaining RIGHT elements.
        while (p2 <= end) {

            temp.push_back(arr[p2]);
            p2++;
        }


        // temp now contains:
        //
        // arr[start ... end]
        //
        // in sorted order.
        //
        // Copy it back into the original array.
        int index = 0;

        for (int i = start; i <= end; i++) {
            arr[i] = temp[index++];
        }
    }


    // ------------------------------------------------------------
    // MERGE SORT
    // ------------------------------------------------------------
    //
    // portion = number of elements in the CURRENT portion.
    //
    // Example:
    //
    // portion = 7
    //
    // left portion  = 7 / 2     = 3
    // right portion = 7 - 3     = 4
    //
    // This is why we don't blindly give both sides portion / 2:
    // an odd-sized portion has one extra element.
    //
    // Base case:
    // portion < 2 means this portion has 0 or 1 element,
    // which is already sorted.
    // ------------------------------------------------------------
    void mergeSort(
        vector<int>& arr,
        int start,
        int end,
        int portion
    ) {

        // One element is already sorted.
        if (portion < 2) {
            return;
        }


        // Number of elements going into LEFT portion.
        int leftPortion = portion / 2;

        // Number of elements going into RIGHT portion.
        int rightPortion = portion - leftPortion;


        // Find ending index of left portion.
        //
        // Example:
        // start = 0
        // leftPortion = 3
        //
        // indexes:
        // 0 1 2
        //
        // mid = 2
        int mid = start + leftPortion - 1;


        // Sort LEFT portion.
        mergeSort(
            arr,
            start,
            mid,
            leftPortion
        );


        // Sort RIGHT portion.
        mergeSort(
            arr,
            mid + 1,
            end,
            rightPortion
        );


        // Both portions are now sorted.
        // Merge them into one larger sorted portion.
        merge(
            arr,
            start,
            end,
            mid
        );
    }


    vector<int> mergeArraysApproach4(vector<vector<int>>& mat) {

        vector<int> answer;


        // Step 1:
        // Flatten all rows into one array.
        for (int row = 0; row < mat.size(); row++) {

            for (int col = 0; col < mat[row].size(); col++) {
                answer.push_back(mat[row][col]);
            }
        }


        // Nothing to sort if there are no elements.
        if (answer.empty()) {
            return answer;
        }


        // Step 2:
        // Apply our own Merge Sort.
        mergeSort(
            answer,
            0,
            answer.size() - 1,
            answer.size()
        );

        return answer;
    }
};
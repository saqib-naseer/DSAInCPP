#include <iostream>
#include <vector>
#include <queue>
using namespace std;


/*
=========================================================
MERGE TWO MAX HEAPS
=========================================================

We have two approaches:

Approach 1:
    Use STL priority_queue (Max Heap).

Approach 2:
    Merge both arrays and manually build a Max Heap
    using bottom-up HeapifyDown.

Important:
    A Max Heap does NOT need to be completely sorted.

    It only needs:
        parent >= left child
        parent >= right child
*/


// =======================================================
// APPROACH 1: USING STL PRIORITY_QUEUE
// =======================================================

vector<int> MergeToMaxHeap(vector<int> arr1, vector<int> arr2)
{
    /*
        priority_queue<int> is a Max Heap by default.

        Push every element from both arrays into it.

        Each push maintains the Max Heap property.
    */
    priority_queue<int> p1;

    vector<int> ans;

    // Insert first heap elements
    for (int i : arr1)
        p1.push(i);

    // Insert second heap elements
    for (int i : arr2)
        p1.push(i);

    /*
        top() always gives the maximum element.

        Since we repeatedly take top() and pop(),
        ans will actually become sorted in
        descending order.

        A descending array is also a valid Max Heap,
        although a Max Heap does NOT need to be sorted.
    */
    while (!p1.empty())
    {
        ans.push_back(p1.top());
        p1.pop();
    }

    return ans;
}


/*
=========================================================
HEAPIFY DOWN
=========================================================

Purpose:
    Restore the Max Heap property starting from 'index'.

Logic:

              current
             /       \
           left      right

1. Assume current is largest.
2. Compare with left child.
3. Compare with right child.
4. Find largest among current, left and right.
5. If current is already largest -> STOP.
6. Otherwise swap with largest child.
7. Continue HeapifyDown from where the value moved.

Time Complexity:
    O(log n)
*/

void heapifydown(int index, vector<int>& ans)
{
    // Assume current node is largest
    int largest = index;

    // Children formulas for 0-based indexing
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Compare left child with largest found so far
    if (left < ans.size() && ans[left] > ans[largest])
        largest = left;

    // Compare right child with largest found so far
    if (right < ans.size() && ans[right] > ans[largest])
        largest = right;

    /*
        If largest == index:
        current node is already >= both children,
        so Max Heap property is satisfied.

        Otherwise swap and follow the moved value down.
    */
    if (largest != index)
    {
        swap(ans[index], ans[largest]);

        index = largest;

        heapifydown(index, ans);
    }
}


// =======================================================
// APPROACH 2: MANUAL BOTTOM-UP BUILD MAX HEAP
// =======================================================

vector<int> MergeToMaxHeap2(vector<int> arr1, vector<int> arr2)
{
    vector<int> ans;

    /*
        STEP 1: Merge both arrays.

        The merged array is NOT necessarily a Max Heap.

        That's okay.

        Build Heap works on an arbitrary/unsorted array.
    */

    for (int i : arr1)
        ans.push_back(i);

    for (int i : arr2)
        ans.push_back(i);


    /*
        STEP 2: Find the LAST NON-LEAF node.

        For a 0-based array:

            lastNonLeaf = (n / 2) - 1

        All indices after this are leaves.

        Leaves don't need HeapifyDown because a node
        with no children is already a valid heap itself.
    */

    int lastNonLeaf = (ans.size() / 2) - 1;


    /*
        STEP 3: Build Max Heap bottom-up.

        Start:

            lastNonLeaf -> ... -> 2 -> 1 -> 0

        Why bottom-up?

        HeapifyDown assumes the child subtrees below
        the current node are already valid heaps.

        Leaves are already heaps.

        So:
            fix parents of leaves first,
            then their parents,
            and finally the root.

        IMPORTANT:

        Outer loop moves:
            bottom -> root

        But each heapifydown() moves:
            parent -> children
    */

    for (int i = lastNonLeaf; i >= 0; i--)
    {
        heapifydown(i, ans);
    }

    return ans;
}


int main()
{
    // Sample Input
    vector<int> a = {2, 5, 1, 9, 12};
    vector<int> b = {3, 7, 4, 10};

    int n = a.size();
    int m = b.size();

    // Using manual HeapifyDown approach
    vector<int> merged = MergeToMaxHeap2(a, b);

    cout << "Merged Max Heap: ";

    for (int i = 0; i < n + m; i++)
        cout << merged[i] << " ";

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

class Heap {
public:
    // Pushes the element at 'index' DOWN until
    // the Max Heap property is restored.
    //
    // lastIndex represents the LAST VALID INDEX
    // of the active heap.
    //
    // Time: O(log n)
    void HeapifyDown(int index, int lastIndex, vector<int>& arr);

    // Converts an unsorted array into a Max Heap
    // using bottom-up Heapify Down.
    //
    // Time: O(n)
    void ConvertToMaxHeap(vector<int>& arr);

    // Sorts array in ascending order using Max Heap.
    //
    // Time: O(n log n)
    void HeapSort(vector<int>& arr);
};


void Heap::ConvertToMaxHeap(vector<int>& arr)
{
    /*
        BUILD MAX HEAP
        --------------

        Array already represents a Complete Binary Tree.

        Leaves are already valid heaps because they have
        no children, so there is no need to heapify them.

        For 0-based indexing:

            Last Non-Leaf = (n / 2) - 1

        Start from the last non-leaf and move BACKWARD
        toward the root.

        Why bottom -> top?

        Before heapifying a parent, we want its child
        subtrees to already be valid heaps.

        NOTE:
        The outer loop moves from bottom -> root,
        but each HeapifyDown() moves an element DOWN.
    */

    int lastNonLeaf = (arr.size() / 2) - 1;

    for (int i = lastNonLeaf; i >= 0; i--)
    {
        HeapifyDown(i, arr.size() - 1, arr);
    }
}


void Heap::HeapifyDown(int index, int lastIndex, vector<int>& arr)
{
    /*
        MAX HEAPIFY DOWN
        ----------------

        Look at:

                  current
                 /       \
               left      right

        Find the LARGEST among:
            current, left, right

        If current is already largest:
            Heap property is satisfied -> STOP.

        Otherwise:
            Swap current with largest child.
            Follow the moved element DOWN.
    */

    int largest = index;

    // 0-based child formulas
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    // Is left child bigger than current?
    if (left <= lastIndex && arr[left] > arr[index])
    {
        largest = left;
    }

    // Compare right with the largest found SO FAR.
    if (right <= lastIndex && arr[right] > arr[largest])
    {
        largest = right;
    }

    /*
        If largest == index, neither child is bigger
        than the current node.

        Therefore this subtree already satisfies
        the Max Heap property.
    */
    if (largest != index)
    {
        swap(arr[index], arr[largest]);

        /*
            The problematic value moved DOWN to 'largest'.

            Follow it and check its new children.
        */
        index = largest;
        HeapifyDown(index, lastIndex, arr);
    }
}


void Heap::HeapSort(vector<int>& arr)
{
    /*
        HEAP SORT
        ---------

        Step 1:
        Convert entire array into a Max Heap.

        Therefore:
            arr[0] = largest element

        Step 2:
        Swap the root (largest) with the LAST element
        of the active heap.

        Step 3:
        That last element is now in its FINAL sorted
        position, so exclude it from the heap.

        Step 4:
        HeapifyDown(0) to restore the Max Heap.

        Repeat until heap size becomes 1.

        Max Heap gives ASCENDING order because we keep
        placing the largest remaining element at the
        right side of the array.
    */

    ConvertToMaxHeap(arr);

    for (int i = arr.size() - 1; i > 0; i--)
    {
        /*
            arr[0] = maximum of active heap.

            Move it to its final position.
        */
        swap(arr[0], arr[i]);

        /*
            Index i is now SORTED.

            Active heap:
                0 ... i-1

            Sorted part:
                i ... n-1

            Therefore lastIndex = i - 1.
        */
        HeapifyDown(0, i - 1, arr);
    }
}


int main()
{
    vector<int> arr =
        {198, 200, 180, 13, 10, 32, 20, 130, 40, 50, 60, 160};

    cout << "Given Array is : \n";

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";

    Heap heap;

    heap.HeapSort(arr);

    cout << "\nAfter Heap Sort Array is : \n";

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
}
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int IterativeBinarySearch(int arr[], int target, int size) {
    int start = 0;
    int end = size - 1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) return mid;
        else if (target > arr[mid]) start = mid + 1;
        else end = mid - 1;
    }
    
    return -1;
}

int RecursiveBinarySearch(int arr[], int target, int start, int end) {
    if (start > end) return -1;
    
    int mid = start + (end - start) / 2;
    
    if (arr[mid] == target) return mid;
    else if (target < arr[mid]) return RecursiveBinarySearch(arr, target, start, mid - 1);
    else return RecursiveBinarySearch(arr, target, mid + 1, end);
}

void merge(int arr[], int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;
    
    vector<int> left(n1), right(n2);
    
    for (int i = 0; i < n1; i++) left[i] = arr[start + i];
    for (int i = 0; i < n2; i++) right[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

void mergeSort(int arr[], int start, int end) {
    if (start >= end) return;
    
    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Data Structures and Algorithms Demo ===" << endl << endl;
    
    cout << "1. Binary Search Demo:" << endl;
    int searchArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13};
    int searchSize = 12;
    cout << "   Array: ";
    printArray(searchArr, searchSize);
    
    int target = 7;
    int result = IterativeBinarySearch(searchArr, target, searchSize);
    cout << "   Searching for " << target << " (iterative): Found at index " << result << endl;
    
    target = 13;
    result = RecursiveBinarySearch(searchArr, target, 0, searchSize - 1);
    cout << "   Searching for " << target << " (recursive): Found at index " << result << endl;
    
    target = 12;
    result = IterativeBinarySearch(searchArr, target, searchSize);
    cout << "   Searching for " << target << ": " << (result == -1 ? "Not found" : "Found") << endl;
    
    cout << endl << "2. Merge Sort Demo:" << endl;
    int sortArr[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int sortSize = 8;
    cout << "   Before sorting: ";
    printArray(sortArr, sortSize);
    
    mergeSort(sortArr, 0, sortSize - 1);
    cout << "   After sorting:  ";
    printArray(sortArr, sortSize);
    
    cout << endl << "=== Demo Complete ===" << endl;
    
    return 0;
}

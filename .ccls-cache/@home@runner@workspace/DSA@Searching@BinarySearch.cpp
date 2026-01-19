#include<iostream>
using namespace std;

// Iterative Binary Search
int IterativeBinarySearch(int arr[], int target, int size) {
	int start = 0;
	int end = size - 1;

	for (int i = 0;i < size;i++) {
		int mid = start + (end - start) / 2;
		if (arr[mid] == target) return mid;
		else if (target > arr[mid]) start = mid + 1;
		else end = mid - 1;
	}

	return -1;
}

//// Recursive Binary Search 
int RecusriveSearch(int arr[], int target, int size, int start, int end) {

	if (start > end) return -1;

	int mid = start + (end - start) / 2;

	if (arr[mid] == target) return mid;
	else if (target < arr[mid]) return RecusriveSearch(arr, target, size, start, mid - 1);
	else return RecusriveSearch(arr, target, size, mid + 1, end);
}

//int main() {
//	int myArray[] = { 1,2,3,4,5,6,7,8,9,10,11,13 };
//
//	cout << RecusriveSearch(myArray, 13, 12, 0, 11);
//
//	//cout << IterativeLinearSearch(myArray, 2, 12);
//
//}
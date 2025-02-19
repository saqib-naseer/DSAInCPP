#include<iostream>
using namespace std;

// Iterative Linear Search
int IterativeLinearSearch(int arr[], int target, int size) {

	for (int i = 0;i < size;i++) {
		if (arr[i] == target) return i;
	}

	return -1;
}

// Recursive Linear 
int RecusriveSearch(int arr[], int target, int size, int index) {

	if (index == size) return -1;
	if (arr[index] == target) return index;


	return RecusriveSearch(arr, target, size, index + 1);
}

//int main() {
//	int myArray[] = { 1,2,3,4,5,6,7,8,9,10,11,13 };
//
//	cout << RecusriveSearch(myArray, 11, 12, 0);
//
//	//cout << IterativeLinearSearch(myArray, 2, 12);
//
//}
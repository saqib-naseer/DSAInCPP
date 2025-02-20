#include<iostream>
#include <vector>

using namespace std;

void merge(int arr[], int start, int mid, int end) {
	vector<int> temp(end - start + 1);
	int index = 0;
	int left = start;
	int right = mid + 1;

	while (left <= mid && right <= end) {
		if (arr[left] < arr[right]) {
			temp[index++] = arr[left++];
		}
		else {
			temp[index++] = arr[right++];
		}
	}

	// If any remaining in left part
	while (left <= mid) {
		temp[index++] = arr[left++];
	}

	// If any remaining in right part
	while (right <= end) {
		temp[index++] = arr[right++];
	}

	// Putting values from temp to original array
	index = 0;
	//for (int i = 0;i < temp.size();i++) {
	//	arr[index] = temp[i];
	//}
	while (start <= end) {
		arr[start++] = temp[index++];
	}
}

void mergeSort(int arr[], int start, int end) {

	if (start == end) return;
	int mid = start + (end - start) / 2;


	// Left
	mergeSort(arr, start, mid);

	// Right
	mergeSort(arr, mid + 1, end);

	// Merge
	merge(arr, start, mid, end);
}



int main() {
	int arr[] = { 12,3,2,5,3,7,3,5,3,5,6,1,7,9,11,2 };
	mergeSort(arr, 0, 15);
	for (int i = 0; i < 15; i++)
	{
		cout << arr[i] << " ";

	}
}
#include <iostream>
using namespace std;

int main() {

	int myArray[] = { 1,2,3,4,5,6,7 };
	cout << recursiveSum(myArray, 0);

	/*recDisplay(myArray, 0);
	* cout << mininumOfArray(myArray, 0);
	for (int i = 0;i < 7;i++) {
		cout << myArray[i] << endl;
	}*/
}

int recursiveSum(int arr[], int index) {
	if (index == 7) return 0;
	return arr[index] + recursiveSum(arr, index + 1);
}

// Get Minium of numbers from array
int mininumOfArray(int arr[], int index) {

	if (index == 7) return arr[6];

	return min(arr[index], mininumOfArray(arr, index + 1));

}

// Display Function
void recDisplay(int arr[], int index) {
	if (index == 7) return;
	cout << arr[index] << endl;
	recDisplay(arr, index + 1);
}


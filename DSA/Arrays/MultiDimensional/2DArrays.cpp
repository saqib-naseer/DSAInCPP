#include <iostream>
using namespace std;

int main() {

	int myarray[3][3] = { 1,2,3,4,5,6,7,8,9 };

	//Traversal
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			cout << myarray[i][j];
		}
	}

	//Diagonal Sum
	int firstDiagonalSum = 0;
	for (int i = 0;i < 3;i++) {
		firstDiagonalSum += myarray[i][i];
	}

	cout << "First Diagonal Sum " << firstDiagonalSum << endl;


}
#include <iostream>
using namespace std;


//int main() {
//
//	int myarray[3][3] = { 1,2,3,4,5,6,7,8,9 };
//
//	for (int i = 0;i < 3;i++) {
//		for (int j = i + 1;j < 3;j++) {
//			swap(myarray[i][j], myarray[j][i]);
//		}
//	}
//
//	cout << "After Transpose" << " ";
//
//	for (int i = 0;i < 3;i++) {
//		for (int j = 0;j < 3;j++) {
//			cout << myarray[i][j] << " ";
//		}
//	}
//
//	cout << "After Reverse" << " ";
//
//	for (int i = 0;i < 3;i++) {
//
//		int start = 0, end = 2;
//
//		while (start < end) {
//			swap(myarray[i][start], myarray[i][end]);
//			start++;
//			end--;
//		}
//
//	}
//
//
//	//Traversal
//	for (int i = 0;i < 3;i++) {
//		for (int j = 0;j < 3;j++) {
//			cout << myarray[i][j] << " ";
//		}
//	}
//
//	////Diagonal Sum
//	//int firstDiagonalSum = 0;
//	//for (int i = 0;i < 3;i++) {
//	//	firstDiagonalSum += myarray[i][i];
//	//}
//
//	//cout << "First Diagonal Sum " << firstDiagonalSum << endl;
//
//
//}
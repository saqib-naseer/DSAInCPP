#include <iostream>
using namespace std;

class Recursion {
public:
	int number = 10;
	void recursion(int num) {
		if (num == 0) return;

		int local = num;

		//cout << number << endl;
		recursion(local - 1);

		while (num > 0) {
			cout << num;
			num--;
		}
		cout << endl;

	}




};

//int main() {
//	Recursion r;
//	r.recursion(5);
//	//recursion(5);
//}




//int main()
//{
//	int x, i = 0;
//	cout << "Enter the number of terms of series : ";
//	cin >> x;
//	cout << "\nFibonnaci Series : ";
//	while (i < x) {
//		cout << " " << fibonacciRecursive(i);
//		i++;
//	}
//
//	fibonacciIterative(10);
//	cout << Exponent(2, 5);
//	cout << factorial(5);
//	function(5);
//}


int fibonacciRecursive(int num) {
	if (num == 0 || num == 1) return num;

	return fibonacciRecursive(num - 1) + fibonacciRecursive(num - 2);
}

void fibonacciIterative(int num) {
	int p = 0, k = 0;
	int j = 1;

	for (int i = 0;i < num;i++) {
		cout << p << " ";
		k = p + j;
		p = j;
		j = k;

		//cout << k << " ";
	}

}

void myRecursiveFunction(int n) {

	if (n == 3)
	{
		cout << "Base Condition Reached n = 3 " << endl;
		return;
	}

	cout << "Calling Function for : " << n << endl;
	myRecursiveFunction(n + 1);
	myRecursiveFunction(n + 1);
	cout << "Returning Function for : " << n << endl;


}

//void function(int n) {
//	if (n == 0) {
//		cout << "Happy Birthday" << endl;
//		return;
//	}
//	cout << n << " Days Left For Birthday" << endl;
//	function(n - 1);
//	//function(n - 1);
//}

void function(int num) {
	if (num == 0)
	{
		return;
	}
	cout << num << endl;
	function(num - 1);
}

int factorial(int num) {
	if (num == 1) {
		return 1;
	}
	return num * factorial(num - 1);
}

int Exponent(int num, int power) {
	if (power == 0) { return 1; }

	return num * Exponent(num, power - 1);
}


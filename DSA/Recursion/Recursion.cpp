#include <iostream>
using namespace std;

void myRecursiveFunction(int n) {

	if (n==10)
	{
		return;
	}

	myRecursiveFunction(n+1);
	cout << n << endl;
}

//int main()
//{
//	 myRecursiveFunction(1);
//}
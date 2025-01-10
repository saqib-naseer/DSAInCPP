#include <iostream>
using namespace std;

void myRecursiveFunction(int n) {

	if (n==3)
	{
		cout << "Base Condition Reached n = 3 " << endl;
		return;
	}

	cout << "Calling Function for : "<<n << endl;
	myRecursiveFunction(n+1);
	myRecursiveFunction(n+1);
	cout << "Returning Function for : " << n << endl;


}

//int main()
//{
//	 myRecursiveFunction(1);
//}
#include <iostream>
using namespace std;



int main() {

}


/*
Pattern1
*
**
***
****
*****
void Pattern1() {
	for (int i = 0;i < 5;i++) {

		for (int j = 0; j < i + 1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}
*/

/*
Pattern2:
1
23
345
4567
56789

void Pattern2() {

	int x = 1;
	for (int i = 1;i <= 5;i++) {

		for (int j = i; j <= x; j++)
		{
			cout << j;
		}
		cout << endl;
		x = x + 2;
	}
}
*/

/*
Pattern 3:
1
2 1
3 2 1
4 3 2 1
5 4 3 2 1

void Pattern3(){
	int num = 1;
	for (int j = 1; j <= 5; j++)
	{
		for (int i = 1;i <= j;i++) {
			cout << num << " ";
			num--;
		}

		num = j + 1;
		cout << endl;
	}

}

*/
#include <iostream>
using namespace std;

//int main() {
//
//}


void DiagonalPattern() {
	/*
	***********
	**       **
	* *     * *
	*  *   *  *
	*   * *   *
	*    *    *
	*   * *   *
	*  *   *  *
	* *     * *
	**       **
	***********
	*/
	for (int i = 0;i <= 10;i++) {

		for (int j = 0;j <= 10;j++) {

			//Space
			/*for (int k = 0;k < i && i != 10 && j != 0;k++) {
				cout << " ";
			}*/

			//if (j > 0 && j < 10) cout << " ";


			//Staric
			if (i == 0 || i == 10 || j == 0
				|| j == 10 || i == j || j == 10 - i) {
				cout << "*";
			}
			else {
				cout << " ";
			}
		}

		cout << endl;

	}
}

/*
Pattern1
*
**
***
****
*****
*/

void Pattern1() {
	for (int i = 0;i < 5;i++) {

		for (int j = 0; j < i + 1; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
}


/*
Pattern2:
1
23
345
4567
56789
*/
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


/*
Pattern 3:
1
2 1
3 2 1
4 3 2 1
5 4 3 2 1
*/
void Pattern3() {
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

void Pattern4() {
	int m = 10;
	for (int i = 0;i < 10;i++) {

		/*for (int k = 1;k <= m;k++) {
			cout << " ";
		}
		m--;*/

		for (int k = 0; k < 10 - i - 1; k++) {
			printf(" ");
		}

		for (int j = 1;j <= 4;j++) {
			cout << "* ";
		}

		cout << endl;
	}
}


void DiamondPattern() {
	int m = 9;
	for (int i = 1;i <= 10;i++) {

		for (int j = 1;j <= m;j++) {
			cout << " ";
		}
		m--;
		for (int k = 1;k <= i; k++) {
			cout << "* ";
		}

		cout << endl;

	}

}

void DiamondPatternReverse() {
	int m = 0;
	for (int i = 10;i >= 1;i--) {

		for (int j = 1;j <= m;j++) {
			cout << " ";
		}
		m++;
		for (int k = 1;k <= i; k++) {
			cout << "* ";
		}

		cout << endl;

	}

}
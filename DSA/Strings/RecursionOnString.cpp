#include<iostream>
using namespace std;


//
//int main() {
//
//	//string name = "orange";
//	//RecursiveReverse(name, 0, name.size() - 1);
//	//cout << name;
//
//	/*string my = "aeiouppppppppppppppppppppi";
//	cout << RecursiveCountVowels(my, my.size() - 1);
//
//
//	string str = "apple";
//	RecursiveChangeLowerToUpper(str, 0);
//	cout << str;*/
//
//	/*string str = "APPLE";
//	RecursiveChangeUpperToLower(str, 0);
//	cout << str;*/
//	//string str = "oMdaMo";
//	//cout << RecursivePalindrome(str, 0, str.size() - 1);
//}

// Recursive Function to reverse a string
void RecursiveReverse(string& s, int start, int end)
{
	if (start > end) return;

	char temp = s[end];
	s[end] = s[start];
	s[start] = temp;

	RecursiveReverse(s, start + 1, end - 1);
}

// Recursively Count Vowels
int RecursiveCountVowels(string str, int index)
{
	if (index == -1) return 0;

	if (str[index] == 'a' || str[index] == 'e'
		|| str[index] == 'i' || str[index] == 'o'
		|| str[index] == 'u') {
		return 1 + RecursiveCountVowels(str, index - 1);
	}
	return  RecursiveCountVowels(str, index - 1);

}

// Recursive Function To Change Lower To Upper
void RecursiveChangeLowerToUpper(string& s, int index) {

	if (index == 5) return;
	char c = s[index] - 'a' + 'A';
	s[index] = c;

	RecursiveChangeLowerToUpper(s, index + 1);
}


// Recursive Function To Change Upper To Lower
void RecursiveChangeUpperToLower(string& s, int index) {

	if (index == 5) return;

	s[index] = s[index] - 'A' + 'a';

	RecursiveChangeUpperToLower(s, index + 1);
}

// Recursive function to Palindrome
bool RecursivePalindrome(string str, int start, int end) {
	if (str[start] != str[end]) return false;
	if (start > end) return true;
	return RecursivePalindrome(str, start + 1, end - 1);
}

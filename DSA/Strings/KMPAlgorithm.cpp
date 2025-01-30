#include <iostream>
#include <vector>
using namespace std;

void ConstructLPS(vector<int>& lpsArray, string s)
{
	int patternSize = s.size();
	int first = 0;
	int second = 1;

	while (second < patternSize) {
		if (s[second] == s[first]) {
			first++;
			lpsArray[second] = first;
			second++;
		}
		else {
			if (first == 0) {
				lpsArray[second] = 0;
				second++;
			}
			else {
				first = lpsArray[first - 1];
			}
		}
	}

}

int FirstMatchingIndex() {
	string hayStack = "ONIONIONIONSIO";
	string needle = "ONIONS";
	int needleSize = needle.size();
	vector<int> LPS(needleSize, 0);
	ConstructLPS(LPS, needle);

	// Return the index of first occurrence if needle exists

	int first = 0;
	int second = 0;
	while (second < needleSize && first < hayStack.size()) {
		if (hayStack[first] == needle[second]) {
			first++;
			second++;
		}
		else {
			if (second == 0) {
				first++;
			}
			else {
				second = LPS[second - 1];
			}

		}
	}

	if (second == needleSize) return first - second;

	return -1;
}

//int main() {
//	cout << "Answer : " << FirstMatchingIndex() << endl;
//
//}


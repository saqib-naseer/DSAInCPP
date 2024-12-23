#include <iostream>
#include <vector>
using namespace std;

void Permute(string s,int k) {
	static int arrayA[] = { 0 ,0,0};
	static vector<char> result(3);

	if (s[k] == '\0') {
		for (int i = 0;i < 3;i++) {
			cout << result[i];
		}
		cout << endl;
	}
	else {
		for (int i = 0;i < 3;i++) {
			if (arrayA[i] == 0) {
				result[k] = s[i];
				arrayA[i] = 1;
				Permute(s, k + 1);
				arrayA[i] = 0;
			}
		}
	}
	
	
}

int main() {
	string s = "ABC";
	
	Permute(s,0);
}


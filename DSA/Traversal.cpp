#include <iostream>
using namespace std;

struct Node {

	int value;
	Node* next;
	
	Node(int value) {
		this->value = value;
		this->next = nullptr;
	}

};

//int main()
//{
//	Node* head = new Node(10);
//	head->next = new Node(20);
//	head->next->next = new Node(30);
//
//	Node* curr = head;
//
//	int n = 5;
//	while (curr!=nullptr) {
//		cout << curr ->value<< endl;
//		curr = curr->next;
//	}
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

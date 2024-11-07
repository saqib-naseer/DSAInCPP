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
//	Node* head = new Node(100);
//	head->next = new Node(200);
//	head->next->next = new Node(300);
//
//	Node* curr = head;
//
//	while (curr != nullptr) {
//		cout << curr->value << endl;
//		curr = curr->next;
//	}
//}
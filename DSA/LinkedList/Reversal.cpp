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
//	head->next->next->next = new Node(400);
//
//	cout<<"Original Linked List"<<endl;
//
//	Node* curr = head;
//
//	while (curr != nullptr) {
//		cout << curr->value << " ";
//		curr = curr->next;
//	}
//
//	curr = head;
//	Node* temp = nullptr;
//	Node* prev = nullptr;
//
//	while (curr != nullptr)
//	{
//		temp = curr->next;
//		curr->next = prev;
//		prev = curr;
//		curr = temp;
//
//	}
//
//	cout << "\nAfter Reversed Linked List" << endl;
//
//	curr = prev;
//
//	while (curr != nullptr) {
//		cout << curr->value << " ";
//		curr = curr->next;
//	}
//
//}
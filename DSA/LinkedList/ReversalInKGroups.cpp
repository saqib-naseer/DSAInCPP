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

void reverseGroup(Node* start, Node* end) {
	Node* curr = start;
	Node* temp = nullptr;
	Node* prev = nullptr;

	while (prev != end)
	{
		temp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = temp;
	}
}


//int main()
//{
//	Node* head = new Node(100);
//	head->next = new Node(200);
//	head->next->next = new Node(300);
//	head->next->next->next = new Node(400);
//	head->next->next->next->next = new Node(500);
//
//	Node* end = head->next->next->next;
//
//	reverseGroup(head,end);
//
//	head;
//	end;
//
//	cout << "Original Linked List" << endl;
//
//	Node* curr = head;
//
//	while (curr != nullptr) {
//		cout << curr->value << " ";
//		curr = curr->next;
//	}



	//cout << "\nAfter Reversed Linked List" << endl;

	/*curr = prev;

	while (curr != nullptr) {
		cout << curr->value << " ";
		curr = curr->next;
	}*/

//}
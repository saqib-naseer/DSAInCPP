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
int calculateLength(Node* head);

Node* removeNthFromEnd(Node* head, int n) {
	int count = 0;
	struct Node* temp = head;
	while (temp) {
		count++;
		temp = temp->next;
	}

	count = count - n - 1;
	if (count == -1) {
		return head->next;
	}

	temp = head;
	while (count > 0) {
		temp = temp->next;
		count--;
	}
	if (temp->next == NULL) {
		return NULL;
	}
	temp->next = temp->next->next;
	return head;
}

int calculateLength(Node* head) {

	int length = 1;
	while (head->next!=nullptr)
	{
		head = head->next;
		length++;
	}
	return length;
}

//int main()
//{
//	Node* head = new Node(100);
//	head->next = new Node(200);
//	/*head->next->next = new Node(300);
//	head->next->next->next = new Node(400);
//	head->next->next->next->next = new Node(500);*/
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
//	Node* returnedHead = removeNthFromEnd(head, 1);
//	cout << "\n After Delete from nth Reverse Linked List" << endl;
//
//	curr = returnedHead;
//
//	while (curr != nullptr) {
//		cout << curr->value << " ";
//		curr = curr->next;
//	}
//}
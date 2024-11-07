#include <iostream>
using namespace std;

struct Node {

	int data;
	Node* next;

	Node(int value) {
		this->data = value;
		this->next = nullptr;
	}

};


bool compare_lists(Node* head1, Node* head2) {
	// Traverse both lists simultaneously
	while (head1 != nullptr && head2 != nullptr) {
		// If the data doesn't match, return false
		if (head1->data != head2->data) {
			return false;
		}
		// Move to the next nodes
		head1 = head1->next;
		head2 = head2->next;
	}

	// If both lists have reached the end, they are equal
	// If one list is longer than the other, return false
	return (head1 == nullptr && head2 == nullptr);
}

int main()
{
	// Linked List 1
	Node* head1 = new Node(10);
	head1->next = new Node(20);
	head1->next->next = new Node(30);

	// Linked List 2
	Node* head2 = new Node(10);
	head2->next = new Node(20);
	head2->next->next = new Node(30);
	head2->next->next->next = new Node(40);

	 cout<<compare_lists(head1, head2);
	 return 0;
}
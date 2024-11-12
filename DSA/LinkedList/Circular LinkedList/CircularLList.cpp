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
void recursiveCircularTraversal(Node* head);

Node* myHead = nullptr;

//int main()
//{
//	Node* head = new Node(10);
//	head->next = new Node(20);
//	head->next->next = new Node(30);
//	head->next->next->next = head;
//
//	Node* curr = head;

	// Iterative Approach
	/*do
	{
		cout << curr->value << endl;
		curr = curr->next;
	}
	while (curr != head);*/

	// Recursive
//	recursiveCircularTraversal(curr);
//}

void recursiveCircularTraversal(Node* head) {

	static int flag = 0;

	if (myHead==nullptr)
	{
		myHead = head;
	}

	if (myHead != head || flag == 0)
	{
	flag++;
	cout << "Flag" << flag << endl;
	cout << head->value << endl;
	recursiveCircularTraversal(head->next);
	}


}
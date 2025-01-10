#include <iostream>
using namespace std;
class Stack {
public:
	int size;
	int* arr;
	int top;

	Stack(int s) {
		size = s;
		top = -1;
		arr = new int[size];
		}

	void push(int value) {
		if (top == size - 1) {
			cout << "Stack Overflow\n";
			return;
		}
		arr[++top] = value;
		cout <<"Pushed value into stack : " << arr[top] << endl;
	}

	void pop() {
		if (top == -1) {
			cout << "Stack underflow" << endl;
		}
		else {
			cout << "Popped value :" << arr[top] << endl;
			top--;
		}
	}

	int peek() {
		if (top == -1) {
			cout << "Stack is empty\n";
		}
		else {
			cout << arr[top] << endl;
		}

	}

	bool isEmpty() {
		if (top == -1) return 1;

		return 0;
	}

	int currentSize() {
		if (top == -1) return 0;
		return top + 1;
	}

	 
};

class Node {
public:
	int data;
	Node* next;
	Node(int value) {
		data = value;
		next = nullptr;
}

};

class StackLL {
public:
	Node* top;
	int size;
	StackLL() {
		top = nullptr;
		size = 0;
	}

	void push(int value) {
		if (top == nullptr) {
			Node* temp = new Node(value);
			top = temp;
		}
		else {
			Node* temp = new Node(value);
			temp->next = top;
			top = temp;
		}
		cout << "Pushed " << value << endl;
		size++;
	}

	void pop() {
		if (top == nullptr) {
			cout << "Stack Underflow\n";
		}
		else {
			Node* temp = top;
			cout << "Popped " << temp->data << endl;
			top = temp->next;
			delete(temp);
			size--;
		}
	}

	int currentSize() {
		return size;
	}
};

int main() {
	// Using Linked List
	StackLL linkedListStack;
	linkedListStack.push(10);
	linkedListStack.push(20);
	linkedListStack.push(30);
	linkedListStack.push(40);
	linkedListStack.push(50);
	cout << "\nCurrent Stack size is " << linkedListStack.currentSize()<<endl;
	linkedListStack.pop();
	linkedListStack.pop();
	linkedListStack.pop();
	cout << "\nCurrent Stack size is " << linkedListStack.currentSize() << endl;
	linkedListStack.pop();
	linkedListStack.pop();
	linkedListStack.pop();
	cout << "\nCurrent Stack size is " << linkedListStack.currentSize() << endl;

	/*
	// Using Arrays
	Stack myStack(5);
	//cout << "Current Size " << myStack.currentSize()<<endl;
	myStack.push(1);
	myStack.push(2);
	//myStack.pop();
	myStack.push(4);
	//cout << "Current Size " << myStack.currentSize() << endl;
	myStack.push(5);
	myStack.push(6);
	myStack.push(7);
	cout << "Current Size " << myStack.currentSize() << endl;*/

}

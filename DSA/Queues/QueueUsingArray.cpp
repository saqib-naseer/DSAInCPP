#include <iostream>
using namespace std;

class Queue {

public:
	int size;
	int rear;
	int front;
	int* arr;
	Queue(int size) {
		this->size = size;
		arr = new int[size];
		rear = front = -1;
	}

	void Enqueue(int value) {
		if (rear == size - 1) {
			cout << "Queue Overflow" << endl;
		}
		else {
			arr[++rear] = value;
			cout << "Enqueued the element : " << value << endl;
		}

	}

	bool IsEmpty() {
		return front == rear;
	}

	void Dequeue() {
		if (IsEmpty()) {
			cout << "Queue underflow" << endl;
		}
		else {
			if (front == rear) {
				front = rear = -1;
			}
			else {
				cout << "Element Dequued " << arr[++front] << endl;
			}
		}


	}

	void Display() {
		if (front == rear) {
			cout << "Queue is Empty" << endl;
		}
		else {
			cout << "Displaying Queue elements " << endl;

			for (int i = front + 1;i <= rear;i++) {
				cout << arr[i];
			}
			cout << '\n';
		}

	}

	void Front() {
		if (front == rear) {
			cout << "Queue is Empty" << endl;
		}
		else {
			cout << "Front Element " << arr[++front] << endl;
		}

	}


};

//int main() {
//	Queue myqueue(5);
//	myqueue.Display();
//	myqueue.Enqueue(1);
//	myqueue.Enqueue(2);
//	myqueue.Enqueue(3);
//	myqueue.Enqueue(4);
//	myqueue.Enqueue(5);
//	myqueue.Front();
//
//	myqueue.Display();
//	myqueue.Dequeue();
//	myqueue.Display();
//	myqueue.Front();
//
//
//
//}
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

// Global variable for tracking the head of the circular list
Node* myHead = nullptr;

void recursiveCircularTraversal(Node* curr) {
    // Base case: Stop recursion when we return to the starting node
    if (curr == nullptr || (myHead != nullptr && curr == myHead)) {
        return;
    }

    // If myHead is uninitialized, set it to the starting node
    if (myHead == nullptr) {
        myHead = curr;
    }

    // Print the current node's value
    cout << curr->value << endl;

    // Recurse to the next node
    recursiveCircularTraversal(curr->next);
}

int main() {
    // Create a circular linked list
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = head; // Make it circular

    // Call recursive function
    recursiveCircularTraversal(head);

    return 0;
}

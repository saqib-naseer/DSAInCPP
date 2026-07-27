#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
  Node(int data) {
    this->data = data;
    this->left = this->right = NULL;
  }
};

int CountLeafNodes(Node *root) {
  if (root == NULL)
    return 0;

  if (root->left == NULL && root->right == NULL)
    return 1;

  return CountLeafNodes(root->left) + CountLeafNodes(root->right);
}

void CountLeafNodesMethod2(Node *root, int &count) {
  if (root == NULL)
    return;

  if (root->left == NULL && root->right == NULL) {
    count++;
    return;
  }
  CountLeafNodesMethod2(root->left, count);
  CountLeafNodesMethod2(root->right, count);
}

void CountNonLeafNodesMethod2(Node *root, int &count) {
  if (root == NULL)
    return;

  if (root->left == NULL && root->right == NULL) {
    return;
  }

  count++;
  CountNonLeafNodesMethod2(root->left, count);
  CountNonLeafNodesMethod2(root->right, count);
}

int CountNonLeafNodesMethod1(Node *root) {
  if (root == NULL)
    return 0;

  if (root->left == NULL && root->right == NULL) {
    return 0;
  }

  return 1 + CountNonLeafNodesMethod1(root->left) +
         CountNonLeafNodesMethod1(root->right);
}

int main() {
  Node *root = new Node(1);
  Node *second = root->left = new Node(2);
  Node *third = root->right = new Node(3);

  second->left = new Node(4);
  second->right = new Node(5);

  third->left = new Node(6);
  third->right = new Node(7);

  cout << "Leaf Nodes Method 1: " << CountLeafNodes(root);

  int count = 0;
  CountLeafNodesMethod2(root, count);
  cout << "\nLeaf Nodes Method 2: " << count;

  count = 0;
  cout << "\nCount reset: " << count;

  cout << "\nNon Leaf Nodes Method 1: " << CountNonLeafNodesMethod1(root);

  CountNonLeafNodesMethod2(root, count);
  cout << "\nNon Leaf Nodes Method 2: " << count;
}

#include <iostream>
#include <queue>
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

void LevelOrder(Node *root) {
  if (root == NULL)
    return;

  queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    Node *temp = q.front();
    q.pop();
    cout << temp->data << " ";
    if (temp->left)
      q.push(temp->left);
    if (temp->right)
      q.push(temp->right);
  }
}

void MirrorBinaryTree(Node *root) {
  if (!root)
    return;

  Node *temp = root->left;
  root->left = root->right;
  root->right = temp;

  MirrorBinaryTree(root->left);
  MirrorBinaryTree(root->right);
}

int main() {
  Node *root = new Node(1);
  Node *second = root->left = new Node(2);
  Node *third = root->right = new Node(3);

  second->left = new Node(4);
  second->right = new Node(5);

  third->left = new Node(6);
  third->right = new Node(7);

  cout << "LevelOrder: " << endl;
  LevelOrder(root);

  MirrorBinaryTree(root);

  cout << "After Mirroring LevelOrder: " << endl;
  LevelOrder(root);
}

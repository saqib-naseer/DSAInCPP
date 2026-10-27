#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>

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

// Prints all leaf nodes of the binary tree.
//
// A leaf node is a node that has:
// left == NULL && right == NULL
//
// Used in Boundary Traversal after printing
// the left boundary.
void PrintLeafNodes(Node* root)
{
    // Empty subtree.
    if (!root)
        return;

    // If current node is a leaf,
    // print it and stop going further.
    if (!root->left && !root->right)
    {
        cout << root->data << " ";
        return;
    }

    // Check leaves in left subtree.
    PrintLeafNodes(root->left);

    // Check leaves in right subtree.
    PrintLeafNodes(root->right);
}


// Prints the LEFT boundary of the tree.
//
// Boundary Traversal order:
//
// Root
// ↓
// Left Boundary (excluding leaves)
// ↓
// Leaf Nodes
// ↓
// Right Boundary (excluding leaves)
//
// Leaf nodes are skipped here because
// PrintLeafNodes() will print them separately.
void PrintLeftBoundary(Node* root)
{
    if (!root)
        return;

    // Do not print leaf nodes here.
    if (!root->left && !root->right)
        return;

    // Print current boundary node.
    cout << root->data << " ";

    // Prefer going left.
    // If left child doesn't exist,
    // the boundary bends towards the right.
    if (root->left)
        PrintLeftBoundary(root->left);
    else
        PrintLeftBoundary(root->right);
}


// Prints the RIGHT boundary of the tree.
//
// Unlike the left boundary,
// nodes are printed AFTER recursion
// so that the order becomes bottom-up.
//
// Example:
//
//      1
//       \
//        2
//         \
//          3
//
// Output:
//
// 3 2 1
//
// (excluding leaf nodes)
void PrintRightBoundary(Node* root)
{
    if (!root)
        return;

    // Do not print leaf nodes.
    if (!root->left && !root->right)
        return;

    // Prefer going right.
    // If right child doesn't exist,
    // continue through the left child.
    if (root->right)
        PrintRightBoundary(root->right);
    else
        PrintRightBoundary(root->left);

    // Print while coming back
    // to achieve bottom-up order.
    cout << root->data << " ";
}

// Alternate: To avoid the first root element while printing the right boundary.
void PrintRightBoundaryMethod2(Node* root, bool isRoot = true)
{
    if (!root)
        return;

    // Don't print leaf nodes.
    if (!root->left && !root->right)
        return;

    // Continue towards the boundary.
    if (root->right)
        PrintRightBoundaryMethod2(root->right, false);
    else
        PrintRightBoundaryMethod2(root->left, false);

    // Skip printing only the original root.
    if (!isRoot)
        cout << root->data << " ";
}
int main() {
  Node *root = new Node(1);
  Node *second = root->left = new Node(2);
  Node *third = root->right = new Node(3);

  Node *four = second->left = new Node(4);
  Node *five = second->right = new Node(5);

  Node *six = third->left = new Node(6);
  Node *seven = third->right = new Node(7);

  Node *eight = four->left = new Node(8);
  Node *nine = four->right = new Node(9);

  Node *ten = five->left = new Node(10);
  Node *eleven = five->right = new Node(11);

  Node *twelve = six->left = new Node(12);
  Node *thirteen = six->right = new Node(13);

  Node *fourteen = seven->left = new Node(14);
  Node *fifteen = seven->right = new Node(15);

  cout << "LevelOrder: " << endl;
  LevelOrder(root);
  
  cout << "\nBoundary Traversal: " << endl;
  cout << root->data << " ";
  PrintLeftBoundary(root->left);
  PrintLeafNodes(root);
  PrintRightBoundary(root->right);
}

#include <iostream>
#include <queue>
#include <stack>

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

int CheckBalancedBT(Node *root) {
  if (!root)
    return 0;

  int leftHeight = CheckBalancedBT(root->left);
  if (leftHeight == -1)
    return -1;

  int rightHeight = CheckBalancedBT(root->right);
  if (rightHeight == -1)
    return -1;

  if (abs(leftHeight - rightHeight) > 1)
    return -1;

  return 1 + max(leftHeight, rightHeight);
}


void SpiralTraversal(Node *root)
{
    // Empty tree
    if (root == NULL)
        return;

    stack<Node*> st1; // Prints Left -> Right
    stack<Node*> st2; // Prints Right -> Left

    // Start with the root
    st1.push(root);

    while (!st1.empty() || !st2.empty())
    {
        // -----------------------------
        // Process current level from st1
        // Print: Left -> Right
        // -----------------------------
        while (!st1.empty())
        {
            Node* current = st1.top();
            st1.pop();

            cout << current->data << " ";

            // Push RIGHT first, then LEFT
            // Because stack is LIFO, LEFT will come out first
            // in the next level.
            if (current->right)
                st2.push(current->right);

            if (current->left)
                st2.push(current->left);
        }

        // -----------------------------
        // Process current level from st2
        // Print: Right -> Left
        // -----------------------------
        while (!st2.empty())
        {
            Node* current = st2.top();
            st2.pop();

            cout << current->data << " ";

            // Push LEFT first, then RIGHT
            // Because stack is LIFO, RIGHT will come out first
            // in the next level.
            if (current->left)
                st1.push(current->left);

            if (current->right)
                st1.push(current->right);
        }
    }
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

  cout << "\nSpiral Traversal: " << endl;
      SpiralTraversal(root);
}

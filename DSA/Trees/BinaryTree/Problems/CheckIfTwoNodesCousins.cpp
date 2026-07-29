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

// Checks whether both nodes have the same immediate parent.
bool IsSameParent(Node *root, int a, int b)
{
    // Empty tree
    if (!root)
        return false;

    // If both children exist, compare their values.
    if (root->left && root->right)
    {
        if (root->left->data == a && root->right->data == b)
            return true;

        if (root->left->data == b && root->right->data == a)
            return true;
    }

    // Otherwise, search in the left and right subtrees.
    // If either subtree finds the parent, return true.
    return IsSameParent(root->left, a, b) ||
           IsSameParent(root->right, a, b);
}


// Checks whether two nodes are on the same level.
bool IsSameLevel(Node *root, int a, int b)
{
    if (!root)
        return false;

    queue<Node*> q;
    q.push(root);

    int level = 0;

    // Stores the level where each node is found.
    int aLevel = -1;
    int bLevel = -1;

    // Standard Level Order Traversal (BFS)
    while (!q.empty())
    {
        int size = q.size();
        level++;

        // Process one complete level.
        while (size--)
        {
            Node *temp = q.front();
            q.pop();

            // Record the level of each node.
            if (temp->data == a)
                aLevel = level;

            if (temp->data == b)
                bLevel = level;

            // Push children for the next level.
            if (temp->left)
                q.push(temp->left);

            if (temp->right)
                q.push(temp->right);
        }

        // If both nodes have been found,
        // simply compare their levels.
        if (aLevel != -1 && bLevel != -1)
        {
            if (aLevel == bLevel)
                return true;
        }
    }

    return false;
}


// Two nodes are cousins if:
// 1. They are on the same level.
// 2. They do NOT have the same parent.
bool AreNodesCousins(Node *root, int a, int b)
{
    if (!root)
        return false;

    return IsSameLevel(root, a, b) &&
           !IsSameParent(root, a, b);
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

  cout << "\nAre Nodes Cousins: " <<(AreNodesCousins(root,5,7) ? "Yes": "No");
        
}

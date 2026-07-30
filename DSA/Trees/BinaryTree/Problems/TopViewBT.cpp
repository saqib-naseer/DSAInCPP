#include <iostream>
#include <queue>
#include <stack>
#include <climits>
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

// Finds the leftmost and rightmost horizontal distance (HD) in the tree.
// Left child decreases HD by 1.
// Right child increases HD by 1.
void FindLeftRightPosition(Node* root, int pos, int& left, int& right)
{
    if (!root)
        return;

    // Update minimum and maximum horizontal distance encountered.
    left = min(left, pos);
    right = max(right, pos);

    // Traverse left subtree.
    FindLeftRightPosition(root->left, pos - 1, left, right);

    // Traverse right subtree.
    FindLeftRightPosition(root->right, pos + 1, left, right);
}

vector<int> TopView(Node* root)
{
    if (!root)
        return {};

    // Determine the horizontal distance range.
    int left = 0;
    int right = 0;
    FindLeftRightPosition(root, 0, left, right);

    cout << "Values Of Left and Right Range "<<left << " " << right << endl;

    // Queue for BFS traversal.
    queue<Node*> nodesQ;

    // Stores horizontal distance index corresponding to each node.
    queue<int> indexQ;

    nodesQ.push(root);

    // Shift index so that negative horizontal distances
    // become valid array indices.
    indexQ.push(-left);

    int level = 0;

    // Stores the minimum level seen for every horizontal distance.
    // (Useful for DFS. In BFS this is technically redundant because
    // BFS already visits shallower nodes first.)
    vector<int> levels(right - left + 1, INT_MAX);

    // Stores the final Top View answer.
    vector<int> ans(right - left + 1, 0);

    while (!nodesQ.empty())
    {
        int size = nodesQ.size();

        // Current BFS level.
        level++;

        while (size--)
        {
            Node* temp = nodesQ.front();
            int index = indexQ.front();

            nodesQ.pop();
            indexQ.pop();

            // Update answer only if this node is at a smaller level
            // than the previously stored node for this column.
            if (level < levels[index])
            {
                levels[index] = level;
                ans[index] = temp->data;
            }

            // Left child belongs to previous horizontal distance.
            if (temp->left)
            {
                nodesQ.push(temp->left);
                indexQ.push(index - 1);
            }

            // Right child belongs to next horizontal distance.
            if (temp->right)
            {
                nodesQ.push(temp->right);
                indexQ.push(index + 1);
            }
        }
    }

    return ans;
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

  /* Random Testing
  fourteen->right = new Node(16);
  fourteen->right->right = new Node(17);
  fourteen->right->right->right = new Node(18);
  fourteen->right->right->right->right = new Node(19);
  fourteen->right->right->right->right->right = new Node(20);
  */
  cout << "LevelOrder: " << endl;
  LevelOrder(root);

  cout << "\nTop View: " <<endl;
  vector<int> ans = TopView(root);

  for(auto i: ans)
    cout<<i<<" ";
  
}

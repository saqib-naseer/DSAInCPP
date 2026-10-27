#include <climits>
#include <iostream>
#include <queue>
#include <vector>
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

void PreOrder(Node *root) {
  if (root == NULL)
    return;
  cout << root->data << " ";
  PreOrder(root->left);
  PreOrder(root->right);
}

vector<int> MaxOnEachLevel(Node *root) {
  vector<int> ans;

  if (root == NULL)
    return ans;

  queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    int size = q.size();
    int maxi = INT_MIN;
    for (int i = 0; i < size; i++) {
      Node *temp = q.front();
      q.pop();
      maxi = max(maxi, temp->data);

      if (temp->left)
        q.push(temp->left);
      if (temp->right)
        q.push(temp->right);
    }
    ans.push_back(maxi);
  }
  return ans;
}

int main() {

  Node *root = new Node(1);
  Node *second = root->left = new Node(2);
  Node *third = root->right = new Node(3);

  second->left = new Node(4);
  second->right = new Node(5);

  third->left = new Node(6);
  third->right = new Node(7);
  cout << "\nPreOrder: " << endl;
  PreOrder(root);
  vector<int> ans = MaxOnEachLevel(root);
  cout << "\nMax on each level: " << endl;

  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << " ";
  }
}

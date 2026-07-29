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

int CheckBalancedBT(Node *root){
  if(!root) return 0;

  int leftHeight = CheckBalancedBT(root->left);
  if(leftHeight == -1) return -1;
  
  int rightHeight = CheckBalancedBT(root->right);
  if(rightHeight == -1) return -1;

   if(abs(leftHeight - rightHeight) > 1) return -1;

  return 1+max(leftHeight, rightHeight);
  
}

int main() {
  Node *root = new Node(1);
  Node *second = root->left = new Node(2);
  Node *third = root->right = new Node(3);

  Node *four = second->left = new Node(4);
  Node *five = second->right = new Node(5);

  Node *six = third->left = new Node(6);
  Node *seven = third->right = new Node(7);

  //Node *eight = four->left = new Node(8);
 // Node *nine = eight->left = new Node(9);
  cout << "LevelOrder: " << endl;
  LevelOrder(root);

  CheckBalancedBT(root)!=-1 ? cout << "Balanced" : cout<<"Unbalanced";
  

}

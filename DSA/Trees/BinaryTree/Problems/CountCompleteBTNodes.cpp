#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
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

int countNodes(Node* root) {
        if(!root) return 0;
        
        int leftHeight =LeftHeight(root);
        int rightHeight =RightHeight(root);
     
        if(leftHeight == rightHeight) return pow(2, leftHeight)-1;

        return 1 + countNodes(root->left)+countNodes(root->right);
    }

    int LeftHeight(Node* root){
        if(!root) return 0;

        return 1 + LeftHeight(root->left);
    }

    int RightHeight(Node* root){
        if(!root) return 0;

        return 1 + RightHeight(root->right);
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
 /* Node *eleven = five->right = new Node(11);

  Node *twelve = six->left = new Node(12);
  Node *thirteen = six->right = new Node(13);

  Node *fourteen = seven->left = new Node(14);
  Node *fifteen = seven->right = new Node(15);

   Node *sixteen = fifteen->right = new Node(16);
   Node *seventeen = sixteen->right = new Node(17);
   Node *eighteen = seventeen->right = new Node(18);
   Node *nineteen = eighteen->right = new Node(19);
  
  Node *twenty = ten->left = new Node(20);
  */
  cout << "LevelOrder: " << endl;
  LevelOrder(root);


}

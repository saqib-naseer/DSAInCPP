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

void MorrisPreOrder(Node* root){
  
	if(!root) return;
	
	while(root){


    
		if(!root->left){    // If left not present, print and move to right
			cout<<root->data<<" ";
      root = root->right;
		}
		else{
			Node* curr = root->left;
			while((curr->right) && !(curr->right==root)){
				curr = curr->right;
			}
			//Not Traversed
			if(!curr->right){
            cout<<root->data<<" ";
				curr ->right = root;
				root = root->left;
			}
			//Already Traversed
			else
      {
				root=root->right;
				curr->right = NULL;
			}	
		}
	
	}

}
void MorrisInOrder(Node* root){
  
	if(!root) return;
	
	while(root){
		if(!root->left){    // If left not present, print and move to right
			cout<<root->data<<" ";
			root = root->right;
		}
		else{
			
			Node* curr = root->left;
			while((curr->right) && !(curr->right==root)){
				curr = curr->right;
			}
			//Not Traversed
			if(!curr->right){
				curr ->right = root;
				root = root->left;
			}
			//Already Traversed
			else
      {
				cout<<root->data<<" ";
				root=root->right;
				curr->right = NULL;
			}	
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
/*
  Node *eight = four->left = new Node(8);
  Node *nine = four->right = new Node(9);

  Node *ten = five->left = new Node(10);
  Node *eleven = five->right = new Node(11);

  Node *twelve = six->left = new Node(12);
  Node *thirteen = six->right = new Node(13);

  Node *fourteen = seven->left = new Node(14);
  Node *fifteen = seven->right = new Node(15);
*/
  cout << "LevelOrder: " << endl;
  LevelOrder(root);
  
  cout << "\nMorris Inorder Traversal: " << endl;
  MorrisInOrder(root);

  cout << "\nMorris Preorder Traversal: " << endl;
  MorrisPreOrder(root);
}

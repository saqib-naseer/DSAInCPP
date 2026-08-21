#include <iostream>
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

Node* insert(Node* root, int value)
{
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
		
    }
	
	return root;
    
}

Node* ConstructBST(vector<int> arr){

Node* root = nullptr;

for(int i=0;i<arr.size();i++){
	root = insert(root,arr[i]);
}

  return root;
}

void preorder(Node* root){

    if (root == nullptr) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root){

    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
int main() {
vector<int> arr = {50, 30, 70, 20, 40, 35, 45, 60, 90, 80};
  Node* root = ConstructBST(arr);
  //Traverse to check
  cout<<"Inorder Traversal: ";
  inorder(root);
  cout<<"\n PreOrder Traversal: ";
  preorder(root);
}

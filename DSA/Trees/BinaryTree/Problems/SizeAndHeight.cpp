#include <iostream>
using namespace std;

struct Node{
int data;
Node* left;
Node* right;
Node(int data){
    this->data = data;
    this->left = this->right = NULL;
}
};

int SizeOfBinaryTreeMethod1(Node* root){

  if(root == NULL) return 0;

  return 1 + SizeOfBinaryTreeMethod1(root->left) + SizeOfBinaryTreeMethod1(root->right);
}


void SizeOfBinaryTreeMethod2(Node* root,int& count){
   if(root == NULL) return;
    count++;
    SizeOfBinaryTreeMethod2(root->left,count);
    SizeOfBinaryTreeMethod2(root->right,count);
}

int HeightOfBinaryTree(Node* root){
  if(root == NULL) return 0;

  return 1 + max(HeightOfBinaryTree(root->left),HeightOfBinaryTree(root->right));
}

int main() {
  Node *root = new Node(1);
  Node *second = root->left = new Node(2);
  Node *third = root->right = new Node(3);

  second->left = new Node(4);
  second->right = new Node(5);

  third->left = new Node(6);
  third->right = new Node(7);
  cout << "Size of Binary Tree Method 1: " << SizeOfBinaryTreeMethod1(root);

  int count=0;
  SizeOfBinaryTreeMethod2(root,count);
  cout << "\nSize of Binary Tree Method 2: " << count;

  cout << "\nHeight of Binary Tree: " << HeightOfBinaryTree(root);
  
}

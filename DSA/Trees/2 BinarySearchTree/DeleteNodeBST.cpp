#include <iostream>
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



  Node* deleteNode(Node* root, int key) {
			if(!root) return NULL;
			
			if(root->data==key){
			
				// Leaf
				if(!root->left &&!root->right){
				delete root;
				return NULL;
				} 
				
				// Two Child
				if(root->left && root->right){
					
					Node* newRoot = FindSmallestInRight(root->right);
					
					root->data = newRoot->data;
					
					root->right = deleteNode(root->right,newRoot->data);
					
					return root;
				} 
				
				// One Child
				if(!root->left){
				Node* temp = root->right;
				delete root;
				return temp;
				} 
				
				if(!root->right){
				Node* temp = root->left;
				delete root;
				return temp;
				} 
			}
  
			if (key < root->val)
			{
				root->left = deleteNode(root->left,key);
			}
			else{
				root->right = deleteNode(root->right,key);
			}
			
			return root;
    }



Node* FindSmallestInRight(Node* root){

	if(!root->left){
		return root;
	}
	
	return FindSmallestInRight(root->left);
}



int main() {
Node* root = new Node(50);
Node* n30 = root->left = new Node(30);
Node* n75 = root->right = new Node(75);

Node* n20 = n30->left = new Node(20);
Node* n40 = n30->right = new Node(40);

Node* n65 = n75->left = new Node(65);
Node* n85 = n75->right = new Node(85);

Node* n10 = n20->left = new Node(10);
Node* n25 = n20->right = new Node(25);

Node* n35 = n40->left = new Node(35);
Node* n45 = n40->right = new Node(45);

Node* n60 = n65->left = new Node(60);
Node* n70 = n65->right = new Node(70);

Node* n80 = n85->left = new Node(80);
Node* n90 = n85->right = new Node(90);

Node* n5 = n10->left = new Node(5);
Node* n15 = n10->right = new Node(15);

Node* n33 = n35->left = new Node(33);
Node* n62 = n60->right = new Node(62);
Node* n82 = n80->right = new Node(82);
Node* n95 = n90->right = new Node(95);
/*
                         50
                   /            \
                 30              75
               /    \          /    \
             20      40       65     85
            /  \    /  \     /  \    / \
          10   25  35  45   60  70  80  90
         / \        /          \       \    \
        5  15      33          62      82    95  */
  

}

#include <iostream>
#include <queue>
using namespace std;

class Node{
	public:
   int data;
		Node* left;
			Node* right;

	Node(int val){
		data = val;
		left = right = NULL;
	}

};

void PreOrder(Node* root){
	if(root==NULL) return;

	cout<<root->data<<" ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void PostOrder(Node* root){
	if(root==NULL) return;

	PostOrder(root->left);
	PostOrder(root->right);
	cout<<root->data<<" ";
}

void InOrder(Node* root){
	if(root==nullptr) return;

	InOrder(root->left);
	cout<<root->data<<" ";
	InOrder(root->right);
}

// Creation Method 1: Using Queue
Node* CreationMethod1(Node* root){
	int x;
	cout<<"Enter value for root node: "<<endl;
	cin>>x;

	if(x==-1) return NULL;
	
	queue<Node*> q;
	if(x!=-1)	q.push(root);

	while(!q.empty()){
		Node* temp = q.front();
		q.pop();
		cout<<"Enter Left Node for "<<temp->data<<endl;
		cin>>x;
		if(x!=-1){
			Node* leftNode = new Node(x);
			temp->left = leftNode;
			q.push(leftNode);
		}
		cout<<"Enter Right Node for "<<temp->data<<endl;
		cin>>x;
		if(x!=-1){
			Node* rightNode = new Node(x);
			temp->right = rightNode;
			q.push(rightNode);
		}
	
	}
	return root;
}

// Creation Method 2: Using Recursion
Node* CreationMethod2(){
	int x;
	cout << "Enter value (-1 for NULL): ";
	cin >> x;

	if (x == -1)
			return NULL;

	Node* temp = new Node(x);

	cout << "Enter Left Node for " << temp->data << endl;
	temp->left = CreationMethod2();

	cout << "Enter Right Node for " << temp->data << endl;
	temp->right = CreationMethod2();

	return temp;
}

void LevelOrder(Node* root){

	queue<Node*> q;
	q.push(root);

	while(!q.empty()){
		Node* temp = q.front();

		q.pop();
		cout<<temp->data<<" ";

		if(temp->left!=NULL) q.push(temp->left);
		if(temp->right!=NULL) q.push(temp->right);

		
	}
	
}


int main(){
	
	Node* root = CreationMethod2();

	// Creation Method 1: Using Queue
	// CreationMethod1(root);

	// Creation Method 2: Using Recursion
	//CreationMethod2();
	
	// PreOrder Traversal
	cout<<"PreOrder Traversal: "<<endl;
	PreOrder(root);

	cout<<"\nInorder Traversal: "<<endl;
	InOrder(root);

	cout<<"\nPostOrder Traversal: "<<endl;
	PostOrder(root);

	cout<<"\nLevelOrder Traversal: "<<endl;
	LevelOrder(root);
}





/*
class Node {
public:
	int data;
	Node* left;
	Node* right;
	Node(int val) {
		data = val;
		left = right = NULL;
	}
};

// Binary Tree Creation Method 2 : // Coder Army -Youtube
Node* BinaryTree(int x) {
	if (x == -1) return NULL;
	Node* temp = new Node(x);
	int value;
	cout << "Enter Left Node For " << x << endl;
	cin >> value;
	temp->left = BinaryTree(value);
	cout << "Enter Right Node For " << x << endl;
	cin >> value;
	temp->right = BinaryTree(value);

	return temp;
}

void PreOrder(Node* root) {
	if (root == NULL)
	{
		return;
	}

	cout << root->data << " ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void PostOrder(Node* root) {
	if (root == NULL)
	{
		return;
	}

	PostOrder(root->left);
	PostOrder(root->right);
	cout << root->data << " ";

}

void InOrder(Node* root) {
	if (root == NULL)
	{
		return;
	}

	InOrder(root->left);
	cout << root->data << " ";
	InOrder(root->right);

}


//int main() {
//
//	queue<Node*> q;
//
//	int x;
//	cout << "Enter Root Node: " << endl;
//	cin >> x;
//	Node* root = new Node(x);
//	q.push(root);
//
//	while (!q.empty()) {
//		Node* temp = q.front();
//		q.pop();
//		int value;
//
//		cout << "Enter Left Element For " << temp->data << endl;
//		cin >> value;
//		if (value != -1)
//		{
//			Node* LeftNode = new Node(value);
//			temp->left = LeftNode;
//			q.push(LeftNode);
//		}
//
//		cout << "Enter Right Element For " << temp->data << endl;
//		cin >> value;
//
//		if (value != -1)
//		{
//			Node* rightNode = new Node(value);
//			temp->right = rightNode;
//			q.push(rightNode);
//		}
//
//
//	}
//
//	cout << "PreOrder : " << endl;
//	PreOrder(root);
//
//	cout << "\nInOrder : " << endl;
//	InOrder(root);
//
//	cout << "\nPostOrder : " << endl;
//	PostOrder(root);
//}

//int main() {
//	int x;
//	cout << "Enter Root Node: " << endl;
//	cin >> x;
//	Node* root = BinaryTree(x);
//
//	cout << "PreOrder : " << endl;
//	PreOrder(root);
//
//	cout << "\nInOrder : " << endl;
//	InOrder(root);
//
//	cout << "\nPostOrder : " << endl;
//	PostOrder(root);
//}

*/
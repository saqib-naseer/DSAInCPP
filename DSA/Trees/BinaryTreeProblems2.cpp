#include <iostream>
#include <queue>
using namespace std;

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

// Check if two binary trees are identical
bool IsIdentical(Node* root1, Node* root2) {
	if (!root1 && !root2) return 1;

	if ((!root1 && root2) || (root1 && !root2)) return 0;

	if (root1->data != root2->data) return 0;


	return IsIdentical(root1->left, root2->left) && IsIdentical(root1->right, root2->right);
}

// Mirror Binary Tree 
void MirrorBinaryTree(Node* root) {
	if (!root) return;


	Node* temp = root->right;
	root->right = root->left;
	root->left = temp;

	MirrorBinaryTree(root->left);
	MirrorBinaryTree(root->right);
}

void LevelOrderTraverse(Node* root) {

	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();

		cout << temp->data << " ";

		if (temp->left)
		{
			q.push(temp->left);
		}
		if (temp->right)
		{
			q.push(temp->right);
		}

	}
}

Node* CreateBinaryTree() {
	Node* root = new Node(1);
	Node* secondNode = new Node(2);
	Node* thirdNode = new Node(3);
	Node* fourthNode = new Node(4);
	Node* fiftNode = new Node(5);
	Node* sixthNode = new Node(6);
	Node* seventhNode = new Node(7);
	Node* eigthNode = new Node(8);
	Node* ninththNode = new Node(9);
	Node* tenthNode = new Node(10);
	Node* eleventhNode = new Node(11);
	Node* twelwethNode = new Node(12);
	Node* thirteenthNode = new Node(13);
	Node* fourteenthNode = new Node(14);
	Node* fifteenthNode = new Node(15);

	// Connect binary tree nodes
	root->left = secondNode;
	root->right = thirdNode;

	secondNode->left = fourthNode;
	secondNode->right = fiftNode;

	thirdNode->left = sixthNode;
	thirdNode->right = seventhNode;

	fourthNode->left = eigthNode;

	fiftNode->left = ninththNode;

	sixthNode->left = tenthNode;
	sixthNode->right = eleventhNode;

	seventhNode->right = twelwethNode;

	ninththNode->right = thirteenthNode;

	twelwethNode->right = fourteenthNode;

	fourteenthNode->left = fifteenthNode;

	return root;
}

Node* CreateBinaryTree2() {
	Node* root = new Node(1);
	Node* secondNode = new Node(2);
	Node* thirdNode = new Node(3);
	Node* fourthNode = new Node(4);
	Node* fiftNode = new Node(5);
	Node* sixthNode = new Node(6);
	Node* seventhNode = new Node(7);
	Node* eigthNode = new Node(8);
	Node* ninththNode = new Node(9);
	Node* tenthNode = new Node(10);
	Node* eleventhNode = new Node(11);
	Node* twelwethNode = new Node(12);
	Node* thirteenthNode = new Node(13);
	Node* fourteenthNode = new Node(14);
	Node* fifteenthNode = new Node(15);

	// Connect binary tree nodes
	root->left = secondNode;
	root->right = thirdNode;

	secondNode->left = fourthNode;
	secondNode->right = fiftNode;

	thirdNode->left = sixthNode;
	thirdNode->right = seventhNode;

	fourthNode->left = eigthNode;

	fiftNode->left = ninththNode;

	sixthNode->left = tenthNode;
	sixthNode->right = eleventhNode;

	seventhNode->right = twelwethNode;

	ninththNode->right = thirteenthNode;

	twelwethNode->right = fourteenthNode;
	fourteenthNode->left = fifteenthNode;


	return root;
}

int main() {

	Node* root1 = CreateBinaryTree();
	Node* root2 = CreateBinaryTree2();

	cout << "Binary Trees Identical : " << IsIdentical(root1, root2);

	cout << "\nBefore Mirror :" << endl;
	LevelOrderTraverse(root1);

	MirrorBinaryTree(root1);

	cout << "\nAfter Mirror :" << endl;
	LevelOrderTraverse(root1);
}





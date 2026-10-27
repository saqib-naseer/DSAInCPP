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

// Find maximum element at each level of Binary Tree
void FindMaximumAtEachLevel(Node* root) {
	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		int levelSize = q.size();
		int maxValue = INT_MIN;

		for (int i = 0;i < levelSize;i++) {

			Node* temp = q.front();
			q.pop();

			maxValue = max(maxValue, temp->data);
			if (temp->left)
			{
				q.push(temp->left);
			}
			if (temp->right)
			{
				q.push(temp->right);
			}
		}

		cout << maxValue << " ";
	}

}


// Find Height Of a Binary Tree
int BinaryTreeHeight(Node* root) {
	if (!root) return 0;

	return 1 + max(BinaryTreeHeight(root->left), BinaryTreeHeight(root->right));
}

// Count Non Leaf Nodes in Binary Tree
int BinaryTreeCountNonLeaf(Node* root) {
	if (!root) return 0;

	if (!root->left && !root->right) return 0;

	return 1 + BinaryTreeCountNonLeaf(root->left) + BinaryTreeCountNonLeaf(root->right);
}

// Count No. Of Leaves in Binary Tree
void BinaryTreeCountLeaves(Node* root, int& count) {
	if (!root) return;

	if (!root->left && !root->right) count++;

	BinaryTreeCountLeaves(root->left, count);
	BinaryTreeCountLeaves(root->right, count);
}

// Count No. Of Leaves in Binary Tree Method 2
int BinaryTreeCountLeavesMethod2(Node* root) {
	if (!root) return 0;

	if (!root->left && !root->right) return 1;

	return BinaryTreeCountLeavesMethod2(root->left) + BinaryTreeCountLeavesMethod2(root->right);
}

// Find Binary Tree Sum
int BinaryTreeSum(Node* root) {
	if (!root) return 0;

	return (root->data + BinaryTreeSum(root->left) + BinaryTreeSum(root->right));
}

// Find Binary Tree Sum Method 2
void BinaryTreeSumMethod2(Node* root, int& sum) {
	if (!root) return;
	sum += root->data;
	BinaryTreeSumMethod2(root->left, sum);
	BinaryTreeSumMethod2(root->right, sum);
}

// Find Binary Tree Size Method 2
int BinaryTreeSize2(Node* root) {
	if (!root) return 0;

	return (1 + BinaryTreeSize2(root->left) + BinaryTreeSize2(root->right));
}

// Find Binary Tree Size Method 1
void BinaryTreeSize(Node* root, int& count) {
	if (!root) return;

	count++;
	BinaryTreeSize(root->left, count);
	BinaryTreeSize(root->right, count);
}

void PreOrder(Node* root) {
	if (!root) return;

	cout << root->data << " ";
	PreOrder(root->left);
	PreOrder(root->right);
}

Node* CreateBinaryTreeSample() {
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

/*
int main() {

	Node* root = CreateBinaryTreeSample();

	PreOrder(root);
	cout << "\nMaximum Elements at each Level : ";
	FindMaximumAtEachLevel(root);
	cout << "\nBinary Tree Height : " << BinaryTreeHeight(root);

	cout << "\nNumber of Non Leaf Nodes : " << BinaryTreeCountNonLeaf(root);

	// Count Leaves In Binary Tree
	int leavesCount = 0;
	BinaryTreeCountLeaves(root, leavesCount);
	cout << "\nNumber of Leaves are : " << leavesCount << endl;

	// Count Leaves In Binary Tree Using Method 2
	cout << "Number Of Leaves Using Method 2 : " << BinaryTreeCountLeavesMethod2(root);

	// Sum Of Binary Tree Method 2
	int sum = 0;
	BinaryTreeSumMethod2(root, sum);
	cout << "\nBinary Tree Sum Method 2 :" << sum;

	// Sum Of Binary Tree
	cout << "\nSum Of Binary Tree : " << BinaryTreeSum(root) << endl;

	// Find Binary Tree Size
	int count = 0;
	BinaryTreeSize(root, count);
	cout << "Binary Tree Size : " << count << endl;
	cout << "Binary Tree Size Method 2: " << BinaryTreeSize2(root) << endl;
}




*/
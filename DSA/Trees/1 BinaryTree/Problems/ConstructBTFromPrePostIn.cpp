#include <iostream>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
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

// Finds the index of 'target' in the inorder array
// between inorderStart and inorderEnd.
int FindRootIndex(int inorderStart,
                  int inorderEnd,
                  int target,
                  vector<int>& inorder)
{
    for (int i = inorderStart; i <= inorderEnd; i++)
    {
        if (inorder[i] == target)
            return i;
    }

    return -1;
}


// Constructs Binary Tree using Preorder and Inorder Traversals.
//
// inorderStart  -> Starting index of current inorder subtree.
// inorderEnd    -> Ending index of current inorder subtree.
// preorderIndex -> Index of current root in preorder traversal.
Node* ConstructBTPreIn(int inorderStart,
                       int inorderEnd,
                       int preorderIndex,
                       vector<int>& preorder,
                       vector<int>& inorder)
{
    // No nodes left in this subtree.
    if (inorderStart > inorderEnd)
        return NULL;

    // Current root always comes from preorder.
    Node* root = new Node(preorder[preorderIndex]);

    // Find this root inside inorder traversal.
    int inorderRootIndex =
        FindRootIndex(inorderStart,
                      inorderEnd,
                      preorder[preorderIndex],
                      inorder);

    // ---------------- LEFT SUBTREE ----------------
    //
    // Preorder:
    // Root -> Left -> Right
    //
    // Therefore, the left subtree always starts
    // immediately after the current root.
    root->left =
        ConstructBTPreIn(inorderStart,
                         inorderRootIndex - 1,
                         preorderIndex + 1,
                         preorder,
                         inorder);

    // ---------------- RIGHT SUBTREE ----------------
    //
    // First calculate how many nodes belong
    // to the left subtree.
    int leftSubtreeSize =
        inorderRootIndex - inorderStart;

    // Skip:
    // 1. Current root
    // 2. Entire left subtree
    //
    // The next preorder element becomes
    // the root of the right subtree.
    root->right =
        ConstructBTPreIn(inorderRootIndex + 1,
                         inorderEnd,
                         preorderIndex + leftSubtreeSize + 1,
                         preorder,
                         inorder);

    return root;
}


// Second Problem
Node* ConstructBTPostIn(int inStart,int inEnd, int pos, vector<int>& post, vector<int>& in){

	if(inStart>inEnd) return NULL;
	
	int rootIndex = FindRootIndex(inStart,inEnd,post[pos],in);
	
	Node* root = new Node(post[pos]);
	
	root->right = ConstructBTPostIn(rootIndex+1,inEnd,pos-1,post,in);
	root->left = ConstructBTPostIn(inStart,rootIndex-1,pos-(inEnd-rootIndex)-1,post,in);
	
	return root;

}
void PostOrder(Node* root){
	
	if(!root) return;
	
	
	PostOrder(root->left);
	PostOrder(root->right);
  cout<<root->data<<" ";
}

void PreOrder(Node* root){
	
	if(!root) return;
	
	cout<<root->data<<" ";
	PreOrder(root->left);
	PreOrder(root->right);

}

void InOrder(Node* root){
	
	if(!root) return;
	
	
	InOrder(root->left);
	cout<<root->data<<" ";
  InOrder(root->right);

}
int main() {

  vector<int> inorder = {4,2,8,5,9,1,6,3,7,10};
  vector<int> preorder = {1,2,4,5,8,9,3,6,7,10};
  vector<int> postorder = {4, 8, 9 ,5 ,2, 6 ,10, 7 ,3 ,1};

  Node *root = ConstructBTPostIn(0,9,9,postorder,inorder);
  cout << "LevelOrder: " << endl;
  LevelOrder(root);
  
 /*  Node *root = ConstructBTPreIn(0,9,0,preorder,inorder);

  
  // For Cross Checking
  cout << "\nPreOrder: " << endl;
  PreOrder(root);
*/
  cout << "\nInOrder: " << endl;
  InOrder(root);

  cout << "\nPostOrder: " << endl;
  PostOrder(root);
}

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


bool checkChildrenSum(TreeNode* root) {
       if(!root) return true;
	   
	   if(!root->left && !root->right) return true;
		
		/*bool isValid=false;
		if(root->left && root->right){
		if(root->data == root->left->data + root->right->data) isValid=true;
		}
		int leftValue=0;
		int rightValue=0;
		if(!root->left){
			rightValue = root->right->data;
			if(root->data == rightValue) isValid=true;
		}
	
		if(!root->right){
			leftValue = root->left->data;
			if(root->data == leftValue) isValid=true;
		}
		*/
		int leftValue = (root->left)?root->left->data : 0 ;
		int rightValue = (root->right)?root->right->data : 0 ;

		bool isValid = (root->data==leftValue+rightValue)?true:false;
		// Or more short you can do this
		//bool isValid = (root->data == leftValue + rightValue);
	
		return isValid && checkChildrenSum(root->left) && checkChildrenSum(root->right);
	}


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

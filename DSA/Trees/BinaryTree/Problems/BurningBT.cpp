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

int Burn(Node* root, int target,int &timer){
	
	if(!root) return 0;
	
	if(root->data == target) return -1;
	
	int left = Burn(root->left,target,timer);
	int right = Burn(root->right,target,timer);
	
	if(left<0){
		timer = max(timer, abs(left)+right);
		return left-1;
	}
	
	if(right<0){	
		timer = max(timer, abs(right)+left);
		return right-1;
	}
	
	return 1 + max(left,right);

}

void FindTargetNode(Node* root, int target,Node*& found){
	if(!root) return;
  
	if(root->data == target) {
    found = root;
    return;
  }
  FindTargetNode(root->left,target,found);
	FindTargetNode(root->right,target,found);
}


int FindTargetNodeHeight(Node* root){
	if(!root) return 0;

	int left = FindTargetNodeHeight(root->left);
	int right = FindTargetNodeHeight(root->right);
	
	return 1+max(left,right);
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
  Node *eleven = five->right = new Node(11);

  Node *twelve = six->left = new Node(12);
  Node *thirteen = six->right = new Node(13);

  Node *fourteen = seven->left = new Node(14);
  Node *fifteen = seven->right = new Node(15);

   Node *sixteen = fifteen->right = new Node(16);
   Node *seventeen = sixteen->right = new Node(17);
   Node *eighteen = seventeen->right = new Node(18);
   Node *nineteen = eighteen->right = new Node(19);
  
  Node *twenty = ten->left = new Node(20);
  
  cout << "LevelOrder: " << endl;
  LevelOrder(root);

  // Burning Tree Approach 1 -Coder Army
  cout << "\nBurning Tree Approach 1 -Coder Army";
  int target = 15;
  int timer = 0;
Burn(root,target,timer);
Node* targetNode = NULL;
FindTargetNode(root,target,targetNode);
int downSideTime = FindTargetNodeHeight(targetNode)-1;
int BurnningTime = max(timer,downSideTime);
  
  cout << "\nAnswer" << BurnningTime<< endl;

  
}

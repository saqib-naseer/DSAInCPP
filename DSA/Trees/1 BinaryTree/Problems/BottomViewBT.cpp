#include <iostream>
#include <queue>
#include <stack>
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

// Finds the leftmost and rightmost horizontal distance (HD) in the tree.
// Left child decreases HD by 1.
// Right child increases HD by 1.
void FindLeftRightPosition(Node* root, int pos, int& left, int& right)
{
    if (!root)
        return;

    // Update minimum and maximum horizontal distance encountered.
    left = min(left, pos);
    right = max(right, pos);

    // Traverse left subtree.
    FindLeftRightPosition(root->left, pos - 1, left, right);

    // Traverse right subtree.
    FindLeftRightPosition(root->right, pos + 1, left, right);
}

void BottomViewRec(Node* root, int index, vector<int>& ans, vector<int>& levels,int level){

	if(root == nullptr) return;
	
	if(level>=levels[index]){
		ans[index] = root->data;
		levels[index] = level;
	}
	
	BottomViewRec(root->left, index-1, ans,levels,level+1);
	BottomViewRec(root->right, index+1, ans,levels,level+1);

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

  /* Random Testing
  fourteen->right = new Node(16);
  fourteen->right->right = new Node(17);
  fourteen->right->right->right = new Node(18);
  fourteen->right->right->right->right = new Node(19);
  fourteen->right->right->right->right->right = new Node(20);
  */
  cout << "LevelOrder: " << endl;
  LevelOrder(root);



  // Recursion Method
  cout << "\nBottom View Recursion Method: " <<endl;
  int left = 0,right = 0;
  FindLeftRightPosition(root,0,left,right);
  cout << "Values Of Left and Right Range "<<left << " " << right << endl;
  vector<int> ans1(right-left+1,0);
  vector<int> levels(right-left+1,INT_MIN);
  BottomViewRec(root,left*-1,ans1,levels,0);

  for(auto i : ans1){
    cout<<i<<" ";
  }
}

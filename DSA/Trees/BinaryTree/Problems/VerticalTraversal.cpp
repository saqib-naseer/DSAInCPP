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

void find(int &l, int& r,int pos, Node* root){
	if(!root) return;
	
	l = min(l,pos);
	r = max(r,pos);
	
	find(l,r,pos-1,root->left);
	find(l,r,pos+1,root->right);
	
 }
 
 vector<int> VerticalBTTraversal(Node* root){
	
	if(!root) return {};
	
	vector<int> ans;
	int l=0;int r=0;
	find(l,r,0,root);
	
	vector<vector<int>> positives(abs(l)+1);
	vector<vector<int>> negatives(abs(r)+1);
	
	queue<Node*> nodeQ;
	queue<int> indexQ;
	nodeQ.push(root);
	indexQ.push(0);
	
	while(!nodeQ.empty()){
	
	Node* temp = nodeQ.front();
	int pos = indexQ.front();
	nodeQ.pop(); indexQ.pop();
	
	if(pos<0){
			negatives[abs(pos)].push_back(temp->data);
	}
	if(pos>=0){
	positives[pos].push_back(temp->data);
	}
		
	if(temp->left){
		nodeQ.push(temp->left);
		indexQ.push(pos-1);
	}
	
	if(temp->right){
		nodeQ.push(temp->right);
		indexQ.push(pos+1);
	}
		
	}
	
	//Starting Negatives
	for(int i=negatives.size()-1; i>=0; i--){
	
	for(int j=0;j<negatives[i].size();j++){
		ans.push_back(negatives[i][j]);
	}
	
	}
	
	//Starting Positives
	for(int i=0; i<positives.size(); i++){
	
	for(int j=0;j<positives[i].size();j++){
		ans.push_back(positives[i][j]);
	}
	
	}
	
	return ans;
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

  cout << "LevelOrder: " << endl;
  LevelOrder(root);

  cout << "\nVertical Traversal: " << endl;
  vector<int> vt = VerticalBTTraversal(root);
  for(int x : vt) cout << x << " ";
  cout << endl;
}

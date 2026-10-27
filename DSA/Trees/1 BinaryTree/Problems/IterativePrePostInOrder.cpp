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

void InOrder(Node* root){

	if(!root) return;
	
	stack<Node*> st;
	stack<int> visited;
	st.push(root);
	visited.push(0);
	
	while(!st.empty()){
		
		Node* temp = st.top();
		int flag = visited.top();
		st.pop();
		visited.pop();
		
		if(!flag){
		
		if(temp->right) {
		visited.push(0);
		st.push(temp->right);
		}
		
		st.push(temp);
		visited.push(1);
		
		if(temp->left){
		st.push(temp->left);
		visited.push(0);
		
		} 
		
		}
		else{
		cout<<temp->data<<" ";
		}
		
		
	}

}

vector<int> PostOrder(Node* root){

	if(!root) return {};
	
	vector<int> ans;
	stack<Node*> st;
	st.push(root);
	
	while(!st.empty()){
		
		Node* temp = st.top();
		st.pop();
		ans.push_back(temp->data);
		if(temp->left) st.push(temp->left);
		if(temp->right) st.push(temp->right);
	}

	reverse(ans.begin(),ans.end());
	
	return ans;
}


void PreOrder(Node* root){

	if(!root) return;
	
	stack<Node*> st;
	st.push(root);
	
	while(!st.empty()){
		
		Node* temp = st.top();
		st.pop();
		cout<<temp->data<<" ";
		if(temp->right) st.push(temp->right);
		if(temp->left) st.push(temp->left);
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

  cout << "\nPreOrder: " <<endl;
  PreOrder(root);

  cout << "\nInOrder: " <<endl;
  InOrder(root);

  cout << "\nPostOrder: " <<endl;
  vector<int> ans = PostOrder(root);
  for(auto i : ans)
    cout<<i<<" ";
  
}

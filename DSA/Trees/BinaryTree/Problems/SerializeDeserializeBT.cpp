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


  // Encodes a tree to a single string.
    string serialize(Node* root) {
        string result;
        helper(root,result);
        return result;
    }

    void helper(Node* root, string& result) {
        if (!root) {
            result += "#,";
            return;
        }

        result += to_string(root->val) + ",";

        helper(root->left, result);
        helper(root->right, result);
    }
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
    cout<<data<<endl;
    vector<string> v;
    stringstream ss(data);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        //int value = stoi(token);
        v.push_back(substr);
      }
      int curr=0;
    return Create(v,curr);
    }

    Node* Create(vector<string>& v,int& curr){
        if(curr>=v.size()) return NULL;
        if(v[curr]=="#") {curr++;
        return NULL;}
        Node* node = new Node(stoi(v[curr]));
        curr++;
        node->left = Create(v,curr);
        node->right = Create(v,curr);

        return node;
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

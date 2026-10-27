#include <iostream>
#include <queue>
#include <stack>

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

void PrintLeftView(Node* root){
    if(!root) return;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()){

        int size = q.size();
        cout<<q.front()->data<<" ";

        while(size--){

            Node* temp = q.front();
            q.pop();
            if(temp->left) q.push(temp->left);
            if(temp->right) q.push(temp->right);
        }
    }
}

void PrintRightView(Node* root){
    if(!root) return;

    queue<Node*> q;
    q.push(root);

    while(!q.empty()){

        int size = q.size();
        cout<<q.front()->data<<" ";

        while(size--){

            Node* temp = q.front();
            q.pop();
          if(temp->right) q.push(temp->right);
            if(temp->left) q.push(temp->left);
        }
    }
}

int CountLevels(Node* root,int currentLevel, int& maxLevel){
  if(!root) return 0;
  
  maxLevel = max(currentLevel, maxLevel);

  CountLevels(root->left, currentLevel +1, maxLevel);
  CountLevels(root->right, currentLevel +1, maxLevel);

  return maxLevel;
}


void PrintLeft2(Node* root,int currentLevel, vector<int>& filled){

  if(!root) return;

  if(filled[currentLevel]==0){
      filled[currentLevel] = 1;
      cout<<root->data<< " ";
  }

  PrintLeft2(root->left,currentLevel+1,filled);
  PrintLeft2(root->right,currentLevel+1,filled);
}


void PrintLeft3(Node* root,int currentLevel, vector<int>& ans){

  if(!root) return;

  if(currentLevel== ans.size()){
      ans.push_back(root->data);
      cout<<root->data<< " ";
  }

  PrintLeft3(root->left,currentLevel+1,ans);
  PrintLeft3(root->right,currentLevel+1,ans);
}

void PrintRight3(Node* root,int currentLevel, vector<int>& ans){

  if(!root) return;

  if(currentLevel== ans.size()){
      ans.push_back(root->data);
      cout<<root->data<< " ";
  }
    PrintRight3(root->right,currentLevel+1,ans);
    PrintRight3(root->left,currentLevel+1,ans);

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

  cout << "\nLeft View: " <<endl;
  PrintLeftView(root);

  cout << "\nRight View: " <<endl;
  PrintRightView(root);

  int maxLevel = 0;
  CountLevels(root, 1, maxLevel);
  cout << "\nTotal Levels: " << maxLevel<<endl;

  vector<int> filled(maxLevel,0);
  cout << "\nLeft View Method 2: "<<endl;
  PrintLeft2(root,0,filled);  

  cout << "\nLeft View Method 3: " <<endl;
  vector<int> ans;
  PrintLeft3(root,0,ans);

  cout << "\nRight View Method 3: " <<endl;
  vector<int> ans2;
  PrintRight3(root,0,ans2);
}

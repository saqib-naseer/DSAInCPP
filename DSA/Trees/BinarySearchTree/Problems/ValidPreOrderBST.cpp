#include <iostream>
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

bool canRepresentBST(vector<int> &arr) {
        // code here
        stack<int> lower;
        stack<int> upper;
        lower.push(INT_MIN);
        upper.push(INT_MAX);
        
        for(int i=0;i<arr.size();i++){
        
            if(arr[i]<lower.top()){
                return 0;
            }    
            
            while(!lower.empty() &&!(arr[i]>lower.top() && arr[i]<upper.top())){
                lower.pop();
                upper.pop();
            }
            
            if(lower.empty()) return 0;
            
            int mini = lower.top();
            int max = upper.top();
            lower.pop();
            upper.pop();
            
            lower.push(arr[i]);
            upper.push(max);
            
            lower.push(mini);
            upper.push(arr[i]);
        }
        
        return 1;
    }


int main() {
Node* root = new Node(50);
Node* n30 = root->left = new Node(30);
Node* n75 = root->right = new Node(75);

Node* n20 = n30->left = new Node(20);
Node* n40 = n30->right = new Node(40);

Node* n65 = n75->left = new Node(65);
Node* n85 = n75->right = new Node(85);

Node* n10 = n20->left = new Node(10);
Node* n25 = n20->right = new Node(25);

Node* n35 = n40->left = new Node(35);
Node* n45 = n40->right = new Node(45);

Node* n60 = n65->left = new Node(60);
Node* n70 = n65->right = new Node(70);

Node* n80 = n85->left = new Node(80);
Node* n90 = n85->right = new Node(90);

Node* n5 = n10->left = new Node(5);
Node* n15 = n10->right = new Node(15);

Node* n33 = n35->left = new Node(33);
Node* n62 = n60->right = new Node(62);
Node* n82 = n80->right = new Node(82);
Node* n95 = n90->right = new Node(95);
/*
                         50
                   /            \
                 30              75
               /    \          /    \
             20      40       65     85
            /  \    /  \     /  \    / \
          10   25  35  45   60  70  80  90
         / \        /          \       \    \
        5  15      33          62      82    95  */
  

}

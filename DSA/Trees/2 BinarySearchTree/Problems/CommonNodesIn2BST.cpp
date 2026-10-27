#include <iostream>
using namespace std;
struct Node {
  int val;
  Node *left;
  Node *right;
  Node(int data) {
    this->data = data;
    this->left = this->right = NULL;
  }
};
// Approach 1
 vector<int> findCommon(Node* r1, Node* r2) {
        // code here
        vector<int> ans;
        vector<int> in1;
        vector<int> in2;
         
        inOrder(in1,r1);
        inOrder(in2,r2);
        
        int j=0;
        
        for(int i=0;i<in1.size()&&j<in2.size();i++){
            // Equal
            // i<j
            // j<i
            if(in1[i]==in2[j]){
                ans.push_back(in1[i]);
                j++;
                continue;
            }
            else if(in1[i]<in2[j]){
                continue;
            }
            else{
                j++;i--;
            }
        }
    
        return ans;
    }
    
    void inOrder(vector<int>& in,Node* root){
        if(!root) return;
        
        inOrder(in,root->left);
        in.push_back(root->data);
        inOrder(in,root->right);
        
    }

// Approach 2
 vector<int> findCommon(Node* r1, Node* r2) {
        // code here
        vector<int> ans;
        
        Node* root1 = r1;
        Node* root2 = r2;
        stack<Node*> st1;
        stack<Node*> st2;
        
        while(root1){
        st1.push(root1);
        root1=root1->left;
        }
        
        while(root2){
        st2.push(root2);
        root2=root2->left;
        }
        
        while(!st1.empty() && !st2.empty()){

            if(st1.top()->data<st2.top()->data){
                root1 = st1.top()->right;
                st1.pop();
            }
            else if(st2.top()->data<st1.top()->data){
                 root2 = st2.top()->right;
                st2.pop();
            }
            else{
                ans.push_back(st1.top()->data);
                root1=st1.top()->right;
                root2=st2.top()->right;
                st1.pop();
                st2.pop();
            }
            
        while(root1){
        st1.push(root1);
        root1=root1->left;
        }
        
        while(root2){
        st2.push(root2);
        root2=root2->left;
        }     
        }

        return ans;
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

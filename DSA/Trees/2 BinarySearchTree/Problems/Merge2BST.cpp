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

    // Push the whole left path
    void pushLeft(Node* root, stack<Node*>& st) {
        while (root) {
            st.push(root);
            root = root->left;
        }
    }

    vector<int> merge(Node* r1, Node* r2) {

        vector<int> ans;

        stack<Node*> st1;
        stack<Node*> st2;

        // Prepare both trees
        pushLeft(r1, st1);
        pushLeft(r2, st2);

        while (!st1.empty() && !st2.empty()) {

            Node* top1 = st1.top();
            Node* top2 = st2.top();

            // Take from tree 1
            if (top1->data < top2->data) {

                ans.push_back(top1->data);
                st1.pop();

                // After ROOT, inorder goes RIGHT
                pushLeft(top1->right, st1);
            }

            // Take from tree 2
            else if (top2->data < top1->data) {

                ans.push_back(top2->data);
                st2.pop();

                pushLeft(top2->right, st2);
            }

            // Equal: take both
            else {

                ans.push_back(top1->data);
                ans.push_back(top2->data);

                st1.pop();
                st2.pop();

                pushLeft(top1->right, st1);
                pushLeft(top2->right, st2);
            }
        }

        // Tree 2 finished, continue tree 1
        while (!st1.empty()) {

            Node* top1 = st1.top();
            st1.pop();

            ans.push_back(top1->data);

            pushLeft(top1->right, st1);
        }

        // Tree 1 finished, continue tree 2
        while (!st2.empty()) {

            Node* top2 = st2.top();
            st2.pop();

            ans.push_back(top2->data);

            pushLeft(top2->right, st2);
        }

        return ans;
    }

// Approach2 
vector<int> merge2(Node *r1, Node *r2) {
        // code here
        vector<int> arr1;
        vector<int> arr2;
        vector<int> ans;
        
        inorder(arr1,r1);
        inorder(arr2,r2);
        
        int i=0,j=0;
        
        while(i<arr1.size() && j<arr2.size()){
            if ( arr1[i]<arr2[j]){
                ans.push_back(arr1[i++]);
            }
            // arr2 < arr1
            else{
                ans.push_back(arr2[j++]);
            }
        }
        
       
        while(i<arr1.size()){
            ans.push_back(arr1[i++]);
        }
        
         while(j<arr2.size()){
            ans.push_back(arr2[j++]);
        }
        
        return ans;
    }
    
    void inorder(vector<int>& ans,Node *r) {
        if(!r) return;
        
        inorder(ans,r->left);
        ans.push_back(r->data);
        inorder(ans,r->right);
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

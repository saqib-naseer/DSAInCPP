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
Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        if(!root) return NULL;

        if(root->data<p->data && root->data<q->data){
            return lowestCommonAncestor(root->right,p,q);
        }
        else if(root->data>p->data && root->data>q->data){
            return lowestCommonAncestor(root->left,p,q);
        }
        else{
            return root;
        }
    }

// Approach 2
Node* lowestCommonAncestor(Node* root,
                               Node* p,
                               Node* q) {

    if (!root)
        return nullptr;

    // Store path from root to p
    vector<Node*> pathP;

    // Store path from root to q
    vector<Node*> pathQ;


    // ---------------------------------
    // Find path from root to p
    // ---------------------------------
    Node* curr = root;

    while (curr) {

        // Current node is part of the path
        pathP.push_back(curr);

        // p is greater, so go right
        if (p->data > curr->data) {
            curr = curr->right;
        }

        // p is smaller, so go left
        else if (p->data < curr->data) {
            curr = curr->left;
        }

        // Found p
        else {
            break;
        }
    }


    // ---------------------------------
    // Find path from root to q
    // ---------------------------------
    curr = root;

    while (curr) {

        pathQ.push_back(curr);

        if (q->data > curr->data) {
            curr = curr->right;
        }

        else if (q->data < curr->data) {
            curr = curr->left;
        }

        // Found q
        else {
            break;
        }
    }


    // ---------------------------------
    // Compare both paths
    // ---------------------------------

    Node* lca = nullptr;
    int i = 0;

    // Continue while BOTH paths have nodes
    while (i < pathP.size() && i < pathQ.size()) {

        // First different node means the paths
        // have separated.
        if (pathP[i] != pathQ[i]) {
            break;
        }

        // They are still common, so remember
        // this as our latest common ancestor.
        lca = pathP[i];

        i++;
    }

    // Last matching node is the LCA
    return lca;
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

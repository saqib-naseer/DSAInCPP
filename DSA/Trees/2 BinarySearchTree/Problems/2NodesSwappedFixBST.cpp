struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class Solution {
public:
  // Approach 2: Using Inorder Traversal With Stack
 void recoverTree2(TreeNode* root) {
        TreeNode* present = NULL;
        TreeNode* prev = NULL;
        TreeNode* first = NULL;
        TreeNode* second = NULL;
        TreeNode* curr = root;
        stack<TreeNode*> st;

        while(curr || !st.empty()){
            
            // put all left in stack
            while(curr){
                st.push(curr);
                curr=curr->left;
            }

            //take inorder element
            TreeNode* temp = st.top();
            st.pop();

            if(prev && prev->val>temp->val){
                if(!first) first = prev;
                second = temp;
            }
            prev = temp;
            curr = temp->right;
        }

        swap(first->val,second->val);
    }
  

  // Approach 1: Using Inorder Morris Traversal 
    void recoverTree(TreeNode* root) {
        TreeNode* present = NULL;
        TreeNode* prev = NULL;
        TreeNode* first = NULL;
        TreeNode* second = NULL;
        TreeNode* curr = NULL;
      

        while(root){

            if(!root->left){
                prev = present;
                present = root;

                if(prev && prev->val>present->val){
                    
                    if(!first) first = prev;

                    second= present;
                }
                root = root->right;
            }
            else{

                curr = root->left;

                while(curr->right && curr->right!=root){
                    curr = curr->right;
                }

                if(!curr->right){
                    curr->right = root;
                    root=root->left;
                }
                else{
                    curr->right = nullptr;
                     prev = present;
                    present = root;

                if(prev && prev->val>present->val){
                    
                    if(!first) first = prev;

                    second= present;
                }
                     root = root->right;   

                }

            }

        }

    int num1 = first->val;
    first->val = second->val;
    second->val = num1;

    }
};
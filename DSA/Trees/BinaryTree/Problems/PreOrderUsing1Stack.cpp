#include <iostream>

     vector<int> preorderTraversal(TreeNode* root) {
      vector<int> ans;
      preHelper(root,ans);
      return ans;
    }

    void preHelper(TreeNode* root,vector<int> &ans){
        if(!root) return;
        
        stack<TreeNode*> st;
        st.push(root);
        ans.push_back(root->val);

        while(root->left){
            st.push(root->left);
            ans.push_back(root->left->val);
            root= root->left;
        }

        while(!st.empty()){
            
            TreeNode* temp = st.top();
            st.pop();

            if(temp->right){

                st.push(temp->right);
                ans.push_back(temp->right->val);
                temp=temp->right;

                while(temp->left){
                ans.push_back(temp->left->val);
                    st.push(temp->left);
                    temp=temp->left;
                }
            }
            else{

            }
        }
    }
int main() {
 
}

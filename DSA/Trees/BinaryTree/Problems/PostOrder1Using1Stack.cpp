#include <iostream>

  vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (!root) return ans;
        postorderHelper(root,ans);
        return ans;
    }

   void postorderHelper(TreeNode* root,vector<int> &ans) {
        
        stack<TreeNode*> st;
        TreeNode* last=nullptr;
        st.push(root);
        
          while(root->left){
                st.push(root->left);
                root = root->left;
            }


        while(!st.empty()){
            TreeNode* temp = st.top(); 
            if(temp->right && last != temp->right){
                temp = temp->right;
                while(temp){
                st.push(temp);
                temp = temp->left;
            }
            }
            else{
                ans.push_back(temp->val);
                last = temp;
                st.pop();
            }
        }
    }

int main() {
 
}

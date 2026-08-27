#include <iostream>

vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(!root) return {};
        InOrder(root,ans);
        return ans;
    }

    void InOrder(TreeNode* root,vector<int>& ans){
        if(!root) return;

        stack<TreeNode*> st;
        BuildLeftSide(root,st);

        while(!st.empty()){
            TreeNode* temp = st.top();
            st.pop();
            ans.push_back(temp->val);
            if(temp->right){
                BuildLeftSide(temp->right,st);
            }

        }
    }

    void BuildLeftSide(TreeNode* root,stack<TreeNode*>& st){

        while(root){
            st.push(root);
            root=root->left;
        }
    }

int main() {
 
}

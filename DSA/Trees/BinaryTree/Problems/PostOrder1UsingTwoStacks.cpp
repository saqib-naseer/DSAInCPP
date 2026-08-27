#include <iostream>

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;

    if (!root)
        return ans;

    postorderHelper(root, ans);
    return ans;
}

void postorderHelper(TreeNode* root, vector<int>& ans) {

    stack<TreeNode*> st1;
    stack<TreeNode*> st2;

    st1.push(root);

    while (!st1.empty()) {

        TreeNode* temp = st1.top();
        st1.pop();

        // Current node goes into second stack
        st2.push(temp);

        // Push LEFT first
        if (temp->left)
            st1.push(temp->left);

        // Push RIGHT second
        if (temp->right)
            st1.push(temp->right);
    }

    // Reverse the order
    while (!st2.empty()) {
        ans.push_back(st2.top()->val);
        st2.pop();
    }
}
int main() {
 
}

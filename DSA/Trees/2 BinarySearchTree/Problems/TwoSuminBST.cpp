/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
  // Approach 2: Using 2 Pointer

bool findTarget(TreeNode* root, int k) {
        if (!root)
            return false;

        vector<int> in;
        vector<int> arr;
        inorder(root, in);
        int i =0;
        int j= in.size()-1;
        while(i<j){
            if(in[i]+in[j]==k) return true;
            if(in[i]+in[j]<k){
                i++;
            }else{
                j--;
            }
        }

        return false;
    }


  // Approach 1:
    bool findTarget(TreeNode* root, int k) {
        if (!root)
            return false;

        vector<int> in;
        vector<int> arr;
        inorder(root, in);
        

        for (int i = 0; i < in.size(); i++) {

            for (int j = i + 1; j < in.size(); j++) {
                if (in[i] + in[j] == k)
                    return true;
            }

        }

        return false;
    }

    void inorder(TreeNode* root, vector<int>& ans) {
        if (!root)
            return;

        inorder(root->left, ans);
        ans.push_back(root->val);
        inorder(root->right, ans);
    }
};
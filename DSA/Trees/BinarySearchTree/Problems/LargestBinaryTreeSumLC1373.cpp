
// Approach 2: A bit short
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct Box{

    bool isBST;
    int sum;
    int min;
    int max;

   Box(bool bst, int s, int mini, int maxi){
    isBST = bst;
    sum = s;
    min = mini;
    max = maxi;
}

};

class Solution {
public:
    int maxSumBST(TreeNode* root) {
        int maxSum =0;
        maxSumBSTHelper(root,maxSum);
        return maxSum;
    }

    Box* maxSumBSTHelper(TreeNode* root,int& maxSum){
       if(!root) return new Box(true,0,INT_MAX,INT_MIN);

        Box* left =  maxSumBSTHelper(root->left,maxSum);
        Box* right =   maxSumBSTHelper(root->right,maxSum);

        if(left->isBST && right->isBST && root->val>left->max && root->val<right->min){
                int sum = root->val + left->sum+right->sum;
                int mini = min(root->val,left->min);
                int maxi = max(root->val,right->max);
                maxSum = max(maxSum, sum);
            return new Box(true,sum,mini,maxi);
        }

        return new Box(0,0,0,false);
    }

};

/// Approach 1: Good but long

struct Box{

    bool isBST;
    int sum;
    int min;
    int max;

    Box(TreeNode* root){
        sum =root->val;
    }

};

class Solution {
public:
    int maxSumBST(TreeNode* root) {
        int maxSum =0;
        maxSumBSTHelper(root,maxSum);
        return maxSum;
    }

    Box* maxSumBSTHelper(TreeNode* root,int& maxSum){
        // Leaf
        if(!root->left && !root->right){
            Box* box = new Box(root);
            box->isBST = true;
            box->min = root->val;
            box->max = root->val;
            maxSum = max(maxSum,box->sum);
            return box;
        }
        //Only Left
        if(!root->right){
           Box* left = maxSumBSTHelper(root->left,maxSum);
           if(left->isBST && root->val>left->max){
                Box* box = new Box(root);
                box->sum += left->sum;
                box->isBST = true;
                box->max = root->val;
                box->min = left->min;
                maxSum = max(maxSum,box->sum);
                return box;
           }
           else{
             left->isBST=false;
            return left;
           }
        }
        //Only Right
        else if(!root->left){
           Box* right = maxSumBSTHelper(root->right,maxSum);
           if(right->isBST && root->val<right->min){
                Box* box = new Box(root);
                box->sum += right->sum;
                box->isBST = true;
                box->min = root->val;
                box->max = right->max;
                maxSum = max(maxSum,box->sum);
                return box;
           }
           else{
             right->isBST=false;
            return right;
           }
        }
        // Both
        else{
           Box* left = maxSumBSTHelper(root->left,maxSum);
           Box* right = maxSumBSTHelper(root->right,maxSum);
            if(left->isBST && right->isBST && root->val<right->min && root->val>left->max){
                Box* box = new Box(root);
                box->isBST = true;
                box->min = left->min;
                box->max = right->max;
                box->sum = left->sum + root->val + right->sum;
                maxSum = max(maxSum,box->sum);
                return box;
            }
            else{
                 left->isBST=false;
                return left;
            }
        }

    }

};
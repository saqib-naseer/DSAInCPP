class Solution {
public:

    /*
        STEP 1: Store BST values using Inorder Traversal.

        Property of BST:
            Inorder traversal gives values in SORTED
            ASCENDING order.

        Example:

                4
               / \
              2   6
             / \ / \
            1  3 5  7

        Inorder:
            [1, 2, 3, 4, 5, 6, 7]

        Time: O(n)
    */
    void inorder(vector<int>& in, Node* root)
    {
        if (!root)
            return;

        inorder(in, root->left);

        in.push_back(root->data);

        inorder(in, root->right);
    }


    /*
        STEP 2: Put sorted values back into the SAME tree
        using POSTORDER traversal.

        Postorder:

            LEFT -> RIGHT -> ROOT

        Our array contains values from smallest -> largest.

        Therefore smaller values are assigned to children
        first, while larger values are assigned to their
        parents later.

        This creates the required Special Max Heap property:

            Every parent is greater than its descendants.

        Important:
            We are NOT changing any pointers/tree structure.
            We only replace node values.

        'ind' is passed by reference because all recursive
        calls must share and advance the same index.
    */
    void construct(Node* root, vector<int>& in, int& ind)
    {
        if (!root)
            return;

        // Fill left subtree first
        construct(root->left, in, ind);

        // Fill right subtree
        construct(root->right, in, ind);

        // Postorder: assign current/root AFTER children
        root->data = in[ind++];
    }


    /*
        BST -> Special Max Heap

        1. Inorder BST
              ↓
           sorted ascending values

        2. Postorder assignment
              ↓
           children receive smaller values first
              ↓
           parents receive larger values later

        Tree structure remains unchanged.
    */
    void convertToMaxHeap(Node* root)
    {
        if (!root)
            return;

        // Get BST values in sorted ascending order
        vector<int> in;

        inorder(in, root);

        // Shared index into sorted array
        int ind = 0;

        // Reassign values in postorder
        construct(root, in, ind);
    }
};
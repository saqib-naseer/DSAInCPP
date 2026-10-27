#include <iostream>
class Solution {
public:

    /*
        STEP 1: Count total nodes.

        Needed for the Complete Binary Tree check.

        For every node:
        count = 1 (current node)
              + nodes in left subtree
              + nodes in right subtree

        Time: O(n)
    */
    int countNodes(Node* root)
    {
        if (!root)
            return 0;

        return 1
             + countNodes(root->left)
             + countNodes(root->right);
    }


    /*
        STEP 2: Check whether tree is a Complete Binary Tree (CBT).

        We assign array-like indexes to tree nodes:

            Root        = 0
            Left child  = 2*i + 1
            Right child = 2*i + 2

        In a Complete Binary Tree containing 'count' nodes,
        every existing node must have an index from:

            0 to count - 1

        If an existing node gets:

            index >= count

        there must be a gap somewhere in the tree,
        therefore it is NOT complete.
    */
    bool isCBT(Node* root, int index, int& count)
    {
        // Empty node does not violate completeness
        if (!root)
            return true;

        // Existing node outside valid index range means a gap exists
        if (index >= count)
            return false;

        // Both left and right subtrees must satisfy CBT condition
        return isCBT(root->left, index * 2 + 1, count) &&
               isCBT(root->right, index * 2 + 2, count);
    }


    /*
        STEP 3: Check Max Heap ordering property.

        For every node:

            parent >= left child
            parent >= right child

        Then recursively verify the same property
        for the complete left and right subtrees.

        Important recursion idea:

        If we find ANY violation -> immediately return false.

        If everything is valid so far -> DO NOT return.
        Continue checking the remaining subtree.

        Only after everything has been checked do we return true.
    */
    bool MaxHeap(Node* root)
    {
        if (!root)
            return true;


        // ---------- Check LEFT child ----------
        if (root->left)
        {
            // Parent must be >= left child
            if (root->data < root->left->data)
                return false;

            /*
                Current parent-left relationship is valid,
                but there may be a violation deeper inside
                the left subtree.

                Ask the left subtree to validate itself.

                If it reports false, propagate false upward.
            */
            if (!MaxHeap(root->left))
                return false;
        }


        // ---------- Check RIGHT child ----------
        if (root->right)
        {
            // Parent must be >= right child
            if (root->data < root->right->data)
                return false;

            /*
                Left side and current-right relationship
                have already been checked.

                Nothing remains after the right subtree,
                so whatever the right subtree returns
                can directly become our answer.
            */
            return MaxHeap(root->right);

            /*
                OR we could write:

                if (!MaxHeap(root->right))
                    return false;

                and then allow execution to reach
                'return true' below.

                Both approaches represent the same idea.
            */
        }

        // Everything reachable from this node is valid
        return true;


        /*
        =====================================================
        ALTERNATIVE / SHORTER APPROACH
        =====================================================

        Same logic can be written more compactly.

        First check the current node against both children.
        A child must exist before accessing child->data.

        if (!root)
            return true;

        if ((root->left &&
             root->data < root->left->data) ||

            (root->right &&
             root->data < root->right->data))
        {
            return false;
        }

        // Current node is valid.
        // Now BOTH subtrees must also be valid.

        return MaxHeap(root->left) &&
               MaxHeap(root->right);


        Mental meaning:

            current node valid
                   AND
            left subtree valid
                   AND
            right subtree valid

        If any one is false -> whole result is false.
        */
    }


    /*
        A Binary Tree is a Max Heap only when BOTH are true:

        1. Tree is a Complete Binary Tree.
        2. Every parent >= its children.

        So:

            isHeap = CBT && MaxHeapProperty
    */
    bool isHeap(Node* tree)
    {
        // Count total nodes
        int count = countNodes(tree);

        // Root starts at array-style index 0
        int index = 0;

        // Check structural property first
        bool res = isCBT(tree, index, count);

        if (!res)
            return false;

        // Structure is complete; now check Max Heap ordering
        return MaxHeap(tree);
    }
};

int main() {

}

/*
auther: Naman Tamrakar
date: 2023-07-23

level: easy
url: https://leetcode.com/problems/search-in-a-binary-search-tree
question: You are given the root of a binary search tree (BST) and an integer val.

Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* searchBST(struct TreeNode* root, int val){
    if (root == '\0')
        return '\0';
    if (val == root->val)
        return root;
    if (val > root->val)
        return searchBST(root->right, val);
    return searchBST(root->left, val);
}


/**
 * Data stored in struct is same as we do in an array but the step size depends on the
 * size of max datatype, for out usecase it is pointer which is 8-bytes, the treenode 
 * buffer would contains value in first 8-bytes, left node address in next 8-bytes and
 * right node address in last 8 bytes.
*/
__attribute__((naked))
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    __asm__(
        "cmpq $0, %rdi;"
        "je if_null;"

        "cmpl (%rdi), %esi;"
        "je if_eq;"

        "cmpl (%rdi), %esi;"
        "jg if_great;"

        "cmpl (%rdi), %esi;"
        "jl if_less;"

    "if_great:;"
        "movl $2, %edx;"    // right
        "movq (%rdi,%rdx,8), %rdi;"
        "call searchBST;"
        "jmp end;"

    "if_less:;"
        "movl $1, %edx;"     // left
        "movq (%rdi,%rdx,8), %rdi;"
        "call searchBST;"
        "jmp end;"

    "if_eq:;"
        "movq %rdi, %rax;"
        "jmp end;"

    "if_null:;"
        "movq %rdi, %rax;"
    "end:;"
        "ret;"
    );
}

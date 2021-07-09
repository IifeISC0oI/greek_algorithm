/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize)
{
    if (postorderSize == 0) {
        return NULL;
    }
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize - 1];

    int rootIndex = 0;
    for (; rootIndex < inorderSize; rootIndex++) {
        if (inorder[rootIndex] == postorder[postorderSize - 1]) {
            break;
        }
    }

    int leftSubTreeNum = rootIndex;
    int rightSubTreeNum = inorderSize - 1 - rootIndex;
    root->left = buildTree(inorder, leftSubTreeNum, postorder, leftSubTreeNum);
    root->right = buildTree(inorder + rootIndex + 1, rightSubTreeNum, postorder + rootIndex, rightSubTreeNum);

    return root;
}

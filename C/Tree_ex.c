//This code is example Funcs of Tree algorithm.
//Example of input and output form is here-

/*
  -input-
  9
  648257913

  -output-
  tree inorder : 1 2 3 4 5 6 7 8 9
  tree preorder : 6 4 2 1 3 5 8 7 9
  tree postorder : 1 3 2 5 4 7 9 8 6
  9개
  height=4
*/

#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
    if (x > y) return x;
    return y;
}

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* setTree(int* arr, int size, int index) {
    int leftIdx, rightIdx;
    TreeNode* newNode;

    newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = arr[index];
    newNode->left = newNode->right = NULL;

    leftIdx = 2 * index + 1;
    rightIdx = leftIdx + 1;

    if (leftIdx < size) newNode->left = setTree(arr, size, leftIdx);
    if (rightIdx < size) newNode->right = setTree(arr, size, rightIdx);

    return newNode;
}

void preorder(TreeNode* root) {
    if (root) {
        printf(" %d", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf(" %d", root->value);
        inorder(root->right);
    }
}

void postorder(TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf(" %d", root->value);
    }
}

int get_node_count(TreeNode* node) {
    int count = 0;
    if (node != NULL) {
        count = 1 + get_node_count(node->left) + get_node_count(node->right);
    }
    return count;
}

int get_node_height(TreeNode* node) {
    int height = 0;
    if (node != NULL) {
        height = 1 + max(get_node_height(node->left), get_node_height(node->right));
    }
    return height;
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%1d", &arr[i]);
    }

    TreeNode* root = NULL;
    root = setTree(arr, n, 0);

    printf("tree inorder :");
    inorder(root);
    printf("\n");

    printf("tree preorder :");
    preorder(root);
    printf("\n");

    printf("tree postorder :");
    postorder(root);
		printf("\n");

		printf("%d개\n", get_node_count(root));
		printf("height=%d",get_node_height(root));

    return 0;
}

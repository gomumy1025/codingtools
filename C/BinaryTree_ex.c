//This code is example Funcs of Binary_Tree algorithm.(Made by GomU)
//Example of input and output form is here:

/*
  -Input-
  7
  6
  1 2
  1 3
  2 4
  3 5
  3 6
  6 7


  -Output-
  Enter number of nodes: 7
  Enter number of edges: 6
  Enter 6 edges (u v) meaning u is parent of v:
  1 2
  1 3
  2 4
  3 5
  3 6
  6 7
  tree preorder : 1 2 4 3 5 6 7
  tree inorder : 4 2 1 5 3 7 6
  tree postorder : 4 2 5 7 6 3 1
  Number of Nodes: 7
  Height: 4
*/

#define _CRT_SECURE_NO_WARNINGS //use this if you are working at Visual Studio!
#include <stdio.h>
#include <stdlib.h>

typedef struct Binary_Tree {
    int value;
    struct Binary_Tree* left;
    struct Binary_Tree* right;
} BT;

BT* nodes[10001];
int isChild[10001]; // 루트 판별용

BT* Create_Node(int val) {
    BT* node = (BT*)malloc(sizeof(BT));
    node->value = val;
    node->left = node->right = NULL;
    return node;
}

void Add_Edge(int u, int v) {
    if (nodes[u] == NULL) nodes[u] = Create_Node(u);
    if (nodes[v] == NULL) nodes[v] = Create_Node(v);

    // 왼쪽 자식이 비었으면 왼쪽에, 아니면 오른쪽에 연결
    if (nodes[u]->left == NULL) nodes[u]->left = nodes[v];
    else if (nodes[u]->right == NULL) nodes[u]->right = nodes[v];
    else printf("Warning: Node %d already has two children!\n", u);

    isChild[v] = 1; // v는 부모가 있음
}

void PreOrder(BT* root) {
    if (root) {
        printf(" %d", root->value);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(BT* root) {
    if (root) {
        InOrder(root->left);
        printf(" %d", root->value);
        InOrder(root->right);
    }
}

void PostOrder(BT* root) {
    if (root) {
        PostOrder(root->left);
        PostOrder(root->right);
        printf(" %d", root->value);
    }
}

int Tree_Node_Count(BT* node) {
    if (node == NULL) return 0;
    return 1 + Tree_Node_Count(node->left) + Tree_Node_Count(node->right);
}

int max(int a, int b) { return (a > b) ? a : b; }

int Tree_Height(BT* node) {
    if (node == NULL) return 0;
    return 1 + max(Tree_Height(node->left), Tree_Height(node->right));
}

int main() {
    int n, m;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &m);

    // 초기화
    for (int i = 1; i <= n; i++) {
        nodes[i] = NULL;
        isChild[i] = 0;
    }

    printf("Enter %d edges (u v) meaning u is parent of v:\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        Add_Edge(u, v);
    }

    // 루트 찾기
    BT* root = NULL;
    for (int i = 1; i <= n; i++) {
        if (!isChild[i] && nodes[i] != NULL) {
            root = nodes[i];
            break;
        }
    }

    if (root == NULL) {
        printf("Error: No root found.\n");
        return 1;
    }

    printf("tree preorder :");
    PreOrder(root);
    printf("\n");

    printf("tree inorder :");
    InOrder(root);
    printf("\n");

    printf("tree postorder :");
    PostOrder(root);
    printf("\n");

    printf("%d개\n", Tree_Node_Count(root));
    printf("height=%d\n", Tree_Height(root));

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int data;
    struct tree_node* right;
    struct tree_node* left;
} TreeNode;

typedef struct thread_node {
    int data;
    struct thread_node* right;
    struct thread_node* left;
    int is_thread;
} ThreadNode;

TreeNode* new_tree_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    return temp;
}

ThreadNode* new_thread_node(int key) {
    ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    temp->is_thread = 0;
    return temp;
}

TreeNode* insert_tree(TreeNode* root, int key) {
    if (root == NULL)
        return new_tree_node(key);

    if (key < root->data)
        root->left = insert_tree(root->left, key);
    else if (key > root->data)
        root->right = insert_tree(root->right, key);

    return root;
}

ThreadNode* insert_thread(ThreadNode* root, int key) {
    if (root == NULL)
        return new_thread_node(key);

    if (key < root->data)
        root->left = insert_thread(root->left, key);
    else if (key > root->data)
        root->right = insert_thread(root->right, key);

    return root;
}

TreeNode* GenerateBinaryTree(int inputData[],int size) {
    TreeNode* root = NULL;

    for (int i = 0; i < size; i++) {
        root = insert_tree(root, inputData[i]);
    }

    return root;
}

void create_threads(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL) return;
    create_threads(root->left, prev);

    if (*prev && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->is_thread = 1;
    }
    *prev = root;
    create_threads(root->right, prev);
}

ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;

    for (int i = 0; i < size; i++) {
        root = insert_thread(root, inputData[i]);
    }

    ThreadNode* prev = NULL;
    create_threads(root, &prev);

    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* curr = root;
    while (curr->left != NULL)
        curr = curr->left;
    while (curr != NULL) {
        printf("%d ", curr->data);
        if (curr->is_thread)
            curr = curr->right;
        else {
            curr = curr->right;
            while (curr && curr->left != NULL)
                curr = curr->left;
        }
    }
}

int main() {
    int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };

    //배열 크기를 생성하고 배열크기를 인자로 주기 위해 다음과 같이 함수를 수정
    //(인자를 주지 않으려면 TreeNode *root = GenerateBinaryTree(inputData);로 수정하고
    // GenerateBinaryTree 함수 안에서 for문의 최대인 size 15로 수정해주면 됨)
    int size = sizeof(inputData) / sizeof(inputData[0]); 
    TreeNode* root = GenerateBinaryTree(inputData, size);

    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);
    return 0;
}

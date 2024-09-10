#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

void GenerateArrayTree(int* tree) {
	//list에 트리 순서에 맞는 수 입력
	int list[] = { 1,2,9,3,5,10,13,4,6,7,8,11,12,14,15 };

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}
	printf("출력결과: \n");
	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n\n");
}

void ArrayPreOrder(int* tree, int index) {
	if (index < 15 && tree[index] != -1) {
		printf("%d ", tree[index]);
		ArrayPreOrder(tree, index * 2 + 1);
		ArrayPreOrder(tree, index * 2 + 2);
	}
}

void ArrayInOrder(int* tree, int index) {
	if (index < 15 && tree[index] != -1) {
		ArrayInOrder(tree, index * 2 + 1);
		printf("%d ", tree[index]);
		ArrayInOrder(tree, index * 2 + 2);
	}
}

void ArrayPostOrder(int* tree, int index) {
	if (index < 15 && tree[index] != -1) {
		ArrayPostOrder(tree, index * 2 + 1);
		ArrayPostOrder(tree, index * 2 + 2);
		printf("%d ", tree[index]);
	}
}

void ArrayOrders(int* tree) {
	ArrayPreOrder(tree, 0);
	printf("\n");
	ArrayInOrder(tree, 0);
	printf("\n");
	ArrayPostOrder(tree, 0);
	printf("\n\n");
}

//노드를 만들고, 입력받은 node의 direction(0:left, 1:right)값에 따라
//올바른 위치에 해당 노드를 배치하는 함수
void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* nd = (TreeNode*)malloc(sizeof(TreeNode));
	nd->data = data;
	nd->left = NULL;
	nd->right = NULL;

	if (direction == 0) {
		node->left = nd;
	}
	else {
		node->right = nd;
	}
}

void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);

	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);

	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* node) {
	if (node != NULL) {
		printf("%d ", node->data);
		LinkPreOrder(node->left);
		LinkPreOrder(node->right);
	}
}

void LinkInOrder(TreeNode* node) {
	if (node != NULL) {
		LinkInOrder(node->left);
		printf("%d ", node->data);
		LinkInOrder(node->right);
	}
}

void LinkPostOrder(TreeNode* node) {
	if (node != NULL) {
		LinkPostOrder(node->left);
		LinkPostOrder(node->right);
		printf("%d ", node->data);
	}
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	printf("\n");
	LinkInOrder(root);
	printf("\n");
	LinkPostOrder(root);
	printf("\n");
}

int main() {
	int arr[15];
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	//각각의 방식(array법, link법)에 따른 트리 생성
	GenerateArrayTree(arr);
	GenerateLinkTree(root);

	//각 생성한 트리를 순회
	ArrayOrders(arr);
	LinkOrders(root);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* stack[MAX_SIZE];
int top = -1;

void push(TreeNode* node) {
	if (top < MAX_SIZE - 1) {
		stack[++top] = node;
		printf("push(%d) ", node->data);
	}
	else {
		printf("Stack Overflow\n");
	}
}

TreeNode* pop() {
	if (top >= 0) {
		printf("pop(%d) ", stack[top]->data);
		return stack[top--];
	}
	else {
		printf("Stack Underflow\n");
		return NULL;
	}
}

int isEmpty() {
	return top == -1;
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

void LinkPreOrder(TreeNode* root) {
	TreeNode* nptr = root;
	printf("전위 순회 출력: \n");
	push(nptr);
	while (!isEmpty()) {
		nptr = pop();
		printf("visit(%d)\n", nptr->data);

		if (nptr->right != NULL) {
			push(nptr->right);
		}

		if (nptr->left != NULL) {
			push(nptr->left);
		}
	}
}

void LinkInOrder(TreeNode* root) {
	TreeNode* nptr = root;
	printf("중위 순회 출력:\n");
	while (nptr != NULL || !isEmpty()) {
		while (nptr != NULL) {
			push(nptr);
			nptr = nptr->left;
		}

		nptr = pop();
		printf("visit(%d)\n", nptr->data);

		nptr = nptr->right;
	}
}

void LinkPostOrder(TreeNode* root) {
	TreeNode* nptr = root;
	TreeNode* lastVisited = NULL;
	printf("후위 순회 출력:\n");

	while (nptr != NULL || !isEmpty()) {
		while (nptr != NULL) {
			push(nptr);
			nptr = nptr->left;
		}

		TreeNode* peek = stack[top];

		if (peek->right == NULL || peek->right == lastVisited) {
			pop();
			printf("visit(%d)\n", peek->data);
			lastVisited = peek;
		}
		else {
			nptr = peek->right;
		}
	}
}


void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	printf("\n");
	LinkInOrder(root);
	printf("\n");
	LinkPostOrder(root);
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	//각각의 방식(link법)에 따른 트리 생성
	//따로 출력은 없는 함수들이다.
	GenerateLinkTree(root);
	//생성한 트리를 스택 반복방식으로 순회
	//순회는 전위,중위,후위 모두 진행
	//이때 모든 push와 pop은 출력
	LinkOrders(root);

	return 0;
}
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

//��带 �����, �Է¹��� node�� direction(0:left, 1:right)���� ����
//�ùٸ� ��ġ�� �ش� ��带 ��ġ�ϴ� �Լ�
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
	printf("���� ��ȸ ���: \n");
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
	printf("���� ��ȸ ���:\n");
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
	printf("���� ��ȸ ���:\n");

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

	//������ ���(link��)�� ���� Ʈ�� ����
	//���� ����� ���� �Լ����̴�.
	GenerateLinkTree(root);
	//������ Ʈ���� ���� �ݺ�������� ��ȸ
	//��ȸ�� ����,����,���� ��� ����
	//�̶� ��� push�� pop�� ���
	LinkOrders(root);

	return 0;
}
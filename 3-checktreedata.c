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
	}
	else {
		printf("Stack Overflow\n");
	}
}

TreeNode* pop() {
	if (top >= 0) {
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

int GetSumOfNodes(TreeNode* root) {
	if (root == NULL) return 0;

	int sum = 0;
	push(root);

	while (!isEmpty()) {
		TreeNode* node = pop();
		sum += node->data;
		if (node->right != NULL) {
			push(node->right);
		}
		if (node->left != NULL) {
			push(node->left);
		}
	}

	printf("Sum of nodes: %d\n", sum);
	return sum;
}

int GetNumberOfNodes(TreeNode* root) {
	if (root == NULL) return 0;

	int count = 0;
	push(root);

	while (!isEmpty()) {
		TreeNode* node = pop();
		count++;
		if (node->right != NULL) {
			push(node->right);
		}
		if (node->left != NULL) {
			push(node->left);
		}
	}

	printf("Number of nodes: %d\n", count);
	return count;
}

int GetHeightOfTree(TreeNode* root) {
	if (root == NULL) return 0;

	int maxHeight = 0;

	typedef struct {
		TreeNode* node;
		int depth;
	} StackBox;

	StackBox stack[MAX_SIZE];
	int top = -1;

	stack[++top] = (StackBox){ root, 1 };

	while (top >= 0) {
		StackBox current = stack[top--];

		if (current.depth > maxHeight) {
			maxHeight = current.depth;
		}
		if (current.node->right != NULL) {
			stack[++top] = (StackBox){ current.node->right, current.depth + 1 };
		}
		if (current.node->left != NULL) {
			stack[++top] = (StackBox){ current.node->left, current.depth + 1 };
		}
	}

	printf("Height of Tree: %d\n", maxHeight);
	return maxHeight;
}


int GetNumberOfLeafNodes(TreeNode* root) {
	if (root == NULL) return 0;

	int leafCount = 0;
	push(root);

	while (!isEmpty()) {
		TreeNode* node = pop();
		if (node->left == NULL && node->right == NULL) {
			leafCount++;
		}
		if (node->right != NULL) {
			push(node->right);
		}
		if (node->left != NULL) {
			push(node->left);
		}
	}

	printf("Number of leaf nodes: %d\n", leafCount);
	return leafCount;
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	//트리생성, 출력은 없는 함수.
	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfTree(root);
	GetNumberOfLeafNodes(root);

	return 0;
}
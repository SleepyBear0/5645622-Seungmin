#include <stdio.h>
#include <stdlib.h>

//Ʈ���� ��� ����ü
typedef struct TreeNode {
    int data; //��忡 ����� ������
    struct TreeNode* left; //���� �ڽ� ���
    struct TreeNode* right;//������ �ڽ� ���
} TreeNode;

int moveCount = 0; //��� �̵� Ƚ��

//���ο� ��带 �����ϴ� �Լ�
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); //�����޸��Ҵ�
    newNode->data = data; //������ ����
    newNode->left = newNode->right = NULL; //�ڽ� ��带 NULL�� �ʱ�ȭ
    return newNode;
}

//���� Ʈ�� ���¸� ����ϴ� �Լ�
TreeNode* currentRoot = NULL; //���� ��Ʈ�� ���� ������ ���

//���� Ʈ���� ���� ������� ����ϴ� �Լ�
void printCurrentTree() {
    if (currentRoot == NULL) return; //Ʈ���� ��������� ����

    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); //ť ����(ť �����Ҵ�)
    int front = 0, rear = 0;

    queue[rear++] = currentRoot; //��Ʈ ��带 ť�� �߰�

    while (front < rear) {
        TreeNode* current = queue[front++]; //ť���� ��� ������
        printf("%d ", current->data); //���� ��� ���

        //���ʰ� ������ �ڽ� ��� ť�� �߰�
        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }

    printf("\n"); //��� �� �� �ٲ�
    free(queue); //ť �޸� ����
}
//������ �����ϴ� �Լ� (��尡 �ִ� ���� ������ �����ϵ���)
void heapify(TreeNode* node) {
    if (node == NULL) return;

    TreeNode* current = node; //���Ե� ��带 �������� ����
    TreeNode* parent = NULL; //�θ� ��带 �����ϱ� ���� ������

    //���Ե� ��� �θ�� ���ϸ鼭 ���� ����
    while (current != currentRoot) {
        parent = currentRoot; //�θ� ��� ã��
        TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); //�θ� ã�⸦ �ϱ� ���� ť
        int front = 0, rear = 0;

        queue[rear++] = parent;

        //�θ� ��带 ã�� ���� Ž��
        while (front < rear) {
            TreeNode* temp = queue[front++];
            if (temp->left == current || temp->right == current) {
                parent = temp; //�θ� ��� �߰�
                break;
            }
            if (temp->left) queue[rear++] = temp->left;
            if (temp->right) queue[rear++] = temp->right;
        }

        free(queue); //ť �޸� ����

        //�θ� �����ϰ� ���� ���(�ڽ�)�� �θ𺸴� ũ�� ��ȯ
        if (parent && current->data > parent->data) {
            int temp = current->data;
            current->data = parent->data;
            parent->data = temp;

            moveCount++; //�̵� Ƚ�� ����

            //Ʈ�� ���� ��� (��ȯ ��)
            printCurrentTree();

            //���� ��带 �θ�� ������Ʈ�Ͽ� �ݺ�
            current = parent;
        }
        else {
            break; //�� �̻� ��ȯ�� �ʿ� ����
        }
    }
}

//���� �� ������ ��迭�ϴ� �Լ� (������ ��Ʈ ��� ��������)
void heapify_del(TreeNode* node) {
    if (node == NULL) return;

    TreeNode* current = node; //��Ʈ ���κ��� ����

    while (1) {
        TreeNode* largest = current;
        TreeNode* leftChild = current->left; //���� �ڽ�
        TreeNode* rightChild = current->right; //������ �ڽ�

        //���� �ڽİ� ���Ͽ� ū �� ã��
        if (leftChild && leftChild->data > largest->data) {
            largest = leftChild;
        }

        //������ �ڽİ� ���Ͽ� ū �� ã��
        if (rightChild && rightChild->data > largest->data) {
            largest = rightChild;
        }

        //���� ���� ��尡 ���� ũ�� ������ ��ȯ
        if (largest != current) {
            //���� ���� ���� ū �ڽ� ��� ��ȯ
            int temp = current->data;
            current->data = largest->data;
            largest->data = temp;

            moveCount++; // �̵� Ƚ�� ����

            //Ʈ�� ���� ��� (��ȯ ��)
            printCurrentTree();

            //��ȯ �� ���� ��带 ���� ū �ڽ����� ������Ʈ �� �ݺ�
            current = largest;
        }
        else {
            break; //�� �̻� ��ȯ�� �ʿ� ����
        }
    }
}

//�ִ� ���� Ʈ���� ��带 �����ϴ� �Լ�
TreeNode* insertMaxHeap(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data); //��Ʈ�� ������ ���ο� ��带 ��Ʈ�� ����
    }

    //���ο� ��带 ����
    TreeNode* newNode = createNode(data);

    //ť�� ����Ͽ� ������ ��ġ�� ã��
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); //ť ���� �Ҵ�
    int front = 0, rear = 0;

    queue[rear++] = root; //��Ʈ ��带 ť�� �߰�

    while (front < rear) {
        TreeNode* current = queue[front++]; //ť���� ��� ������

        //���� �ڽ��� ��� ������ ���⿡ ���ο� ��带 ����
        if (current->left == NULL) {
            current->left = newNode;
            break;
        }
        else {
            queue[rear++] = current->left; //���� �ڽ� ��带 ť�� �߰�
        }

        //������ �ڽ��� ��� ������ ���⿡ ���ο� ��带 ����
        if (current->right == NULL) {
            current->right = newNode;
            break;
        }
        else {
            queue[rear++] = current->right; //������ �ڽ� ��带 ť�� �߰�
        }
    }

    free(queue); //�޸� ����

    printCurrentTree(); //���� ���� ���� �� Ʈ�� ���

    //���� ���� ���� (���ο� ��带 ������ ��)
    heapify(newNode); //���ο� ��带 �������� ���� ����

    return root;
}

//�ִ� �������� ��Ʈ ��带 �����ϴ� �Լ�
TreeNode* deleteRoot(TreeNode* root) {
    if (root == NULL) return NULL;

    //��Ʈ ��带 �����ϰ� ������ ��带 ã�� ���� Ž��
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    TreeNode* lastNode = NULL;
    TreeNode* parent = NULL;

    while (front < rear) {
        lastNode = queue[front++]; //ť���� ������ ��� ������

        if (lastNode->left) {
            queue[rear++] = lastNode->left; //���� �ڽ� ��带 ť�� �߰�
        }
        if (lastNode->right) {
            queue[rear++] = lastNode->right; //������ �ڽ� ��带 ť�� �߰�
        }
    }

    //��Ʈ ����� �����Ϳ� ������ ����� �����͸� ����
    root->data = lastNode->data;

    //������ ��带 ����
    front = 0; rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        parent = queue[front++];

        if (parent->left == lastNode) {
            parent->left = NULL; //���� �ڽ� ����
            break;
        }
        else if (parent->right == lastNode) {
            parent->right = NULL; //������ �ڽ� ����
            break;
        }

        if (parent->left) queue[rear++] = parent->left; //���� �ڽ� ť�� �߰�
        if (parent->right) queue[rear++] = parent->right; //������ �ڽ� ť�� �߰�
    }

    free(lastNode); //������ ��� �޸� ����

    printCurrentTree(); //���� ���� ���� �� Ʈ�� ���

    moveCount = 1; //�̵� Ƚ�� �ʱ�ȭ

    heapify_del(root); //���ο� ��Ʈ�� �������� ���� ����

    free(queue); //�޸� ����

    return root;
}

// Ʈ���� �������� ����ϴ� �Լ�
void printLevelOrder(TreeNode* root, int level) {
    if (root == NULL) return; //��尡 NULL�̸� ����

    if (level == 1)
        printf("%d ", root->data); //���� ������ 1�̸� ���� ����� ������ ���
    else {
        //��������� ���ʰ� ������ �ڽ��� Ž���Ͽ� ������ �´� ��� ���
        printLevelOrder(root->left, level - 1);
        printLevelOrder(root->right, level - 1);
    }
}

// Ʈ���� ���̸� ����ϴ� �Լ�
int height(TreeNode* root) {
    if (root == NULL) return 0; //��尡 NULL�̸� 0����(���̰� 0)
    //���ʰ� ������ ����Ʈ���� ���̸� ��������� ����� ��, �� ū ���� 1�� ���� ��ȯ
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

//Ʈ���� ������ ��ȸ ��� �Լ�
void levelOrder(TreeNode* root) {
    int i;
    int h = height(root); //Ʈ���� ����
    //������ ��� ���
    for (i = 1; i <= h; i++) {
        printf("[%d] ", i);
        printLevelOrder(root, i);
        printf("\n");
    }
    printf("\n");
}

//���� �������̽� �Լ�
void runUserInterface(TreeNode* root) {
    char command; //����ڰ� �Է��� ��ɾ� ����
    int data; //������ ��� ������ ����

    currentRoot = root; //�������� currentRoot�� root�� �ʱ�ȭ

    //c�� �Է��ϱ� ������ ���ѹݺ�
    while (1) {
        printf("�ѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
        printf("| i\t : ��� �߰�\t|\n");
        printf("| d\t : ��� ����\t|\n");
        printf("| p\t : ������ ���\t|\n");
        printf("| c\t : ����\t\t|\n");
        printf("�ѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n");

        printf("�޴� �Է�: ");
        scanf_s(" %c", &command); //��ɾ� �ޱ�

        switch (command) {
        case 'i': //i�� �Է����� ���(����)
            printf("�߰��� �� �Է�: ");
            scanf_s("%d", &data);
            moveCount = 0; //�̵� Ƚ�� �ʱ�ȭ
            root = insertMaxHeap(root, data); //�Էµ� ������ ������ ����
            printf("��尡 �̵��� Ƚ��: %d\n\n", moveCount); //�̵� Ƚ�� ���
            break;
        case 'd': //d�� �Է����� ���(����)
            moveCount = 0; //�̵� Ƚ�� �ʱ�ȭ
            root = deleteRoot(root); //���� �Լ� ȣ��
            printf("��尡 �̵��� Ƚ��: %d\n\n", moveCount);
            break;
        case 'p': //p�� �Է����� ���(���)
            printf("Ʈ�� ������ ���\n");
            levelOrder(root); //levelOrder ȣ��
            break;
        case 'c': //c�� �Է����� ���(����)
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� ����Դϴ�. �ٽ� �Է��ϼ���.\n"); //�߸��� ����� ���� ���
        }
    }
}

// �ʱ� �����͸� �̿��Ͽ� �ִ� ���� Ʈ�� �����ϴ� �Լ�
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = createNode(90); //��Ʈ ��� ����

    //�ڽ� ��� ����
    root->left = createNode(89);
    root->right = createNode(70);

    root->left->left = createNode(36);
    root->left->right = createNode(75);

    root->right->left = createNode(63);
    root->right->right = createNode(13);

    root->left->left->left = createNode(21);
    root->left->left->right = createNode(18);

    root->left->right->left = createNode(5);

    return root;
}

int main() {
    //pdf��°���� Ʈ���� ������ ���� �ٸ�! => pdf Ʈ�� �������� ������ �Է�!!
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]); //�迭�� ũ��

    //Ʈ�� ����
    TreeNode* root = generateMaxHeapTree(inputData, size);

    //���� �������̽� ����
    runUserInterface(root);

    //�޸� ����
    free(root);
    return 0;
}
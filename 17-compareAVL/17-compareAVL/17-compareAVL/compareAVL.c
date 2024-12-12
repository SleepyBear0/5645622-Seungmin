#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//��� ����ü ����
typedef struct Node {
    int key;
    struct Node* left; //���� �ڽ� ���
    struct Node* right; //������ �ڽ� ���
    int height; // AVL Ʈ���� ���� ���� ����
} Node;

//���� ���� �ʱ�ȭ
int compareCount = 0; //Ž�� �� �� Ƚ��
int searchCount = 0;  //Ž�� Ƚ��

//�� ���� �� �� ū ���� ��ȯ�ϴ� �Լ�
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

//����� ���� ��ȯ�ϴ� �Լ�
int getHeight(Node* node) {
    return node ? node->height : 0;
}

//���������� ȸ���ϴ� �Լ�
Node* rightRotate(Node* y) {
    Node* x = y->left; //y�� ���� �ڽ��� x�� ����
    Node* T2 = x->right; //x�� ������ �ڽ��� T2�� ����

    //ȸ��
    x->right = y;
    y->left = T2;

    //����
    y->height = maxValue(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maxValue(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

//�������� ȸ���ϴ� �Լ�
Node* leftRotate(Node* x) {
    Node* y = x->right; //x�� ������ �ڽ��� y�� ����
    Node* T2 = y->left; //y�� ���� �ڽ��� T2�� ����

    //ȸ��
    y->left = x;
    x->right = T2;

    //����
    x->height = maxValue(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maxValue(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

//���� ��� �Լ�
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

//Ʈ������ �ּҰ� ��� ã��
Node* getMinValueNode(Node* node) {
    Node* current = node;

    //���� ���� ��� Ž��
    while (current->left != NULL)
        current = current->left;
    return current;
}

//AVL Ʈ���� ��� �����ϴ� �Լ�
Node* insertAVL(Node* node, int key) {
    //���� Ž�� Ʈ�� ����
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1; //�� ��� ���̴� 1
        return newNode;
    }

    if (key < node->key) {
        node->left = insertAVL(node->left, key); //���� ����Ʈ���� ����
    }
    else if (key > node->key) {
        node->right = insertAVL(node->right, key); //������ ����Ʈ���� ����
    }
    else {
        return node; //�ߺ� Ű�� �������� ����
    }

    //����
    node->height = 1 + maxValue(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    //�ұ��� �ذ�
    //LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    //RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    //LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//AVL Ʈ������ ��� �����ϴ� �Լ�
Node* deleteAVL(Node* root, int key) {
    //���� Ž�� Ʈ�� ����
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteAVL(root->left, key);
    else if (key > root->key)
        root->right = deleteAVL(root->right, key);
    else {
        //��� ����
        if ((root->left == NULL) || (root->right == NULL)) { //�ڽ� ��尡 �Ѱ�
            Node* temp = root->left ? root->left : root->right; //�� �ڽĳ�带 temp�� ����Ŵ
            if (temp == NULL) { //�ڽ� ��尡 ����
                temp = root; //�޸� ����
                root = NULL; //����
            }
            else { //�ڽ� ��尡 �ϳ� ����
                *root = *temp; //�ϳ� �ִ� �ڽ��� �θ�� ��ġ��
            }
            free(temp);
        }
        else {
            //������ ����Ʈ������ �ּҰ� ��� ã��
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    //����
    root->height = 1 + maxValue(getHeight(root->left), getHeight(root->right));
    
    //�����μ�
    int balance = getBalance(root);

    //���� ���� ȸ�� ����
    //R
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    //LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //L
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    //RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//���� Ž�� Ʈ�� ���� �Լ�
Node* insertBST(Node* root, int key) {
    if (root == NULL) {
        //Ʈ���� ��� ������ ���ο� ��� ����
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key; //Ű����
        newNode->left = newNode->right = NULL; //�ڽĳ��� NULL
        return newNode;
    }

    //�����Ϸ��� Ű�� ���� ��庸�� ������ ���� ����Ʈ���� ũ�� ������ ����Ʈ���� ����
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);

    return root;
}

//���� Ž�� Ʈ�� ���� �Լ�
Node* deleteBST(Node* root, int key) {
    if (root == NULL) return root; //Ʈ�ΰ� ��� ������ NULL

    //�����Ϸ��� Ű�� ���� ��庸�� ������ ���� ����Ʈ������ ũ�� ������ ����Ʈ������ ����
    if (key < root->key)
        root->left = deleteBST(root->left, key);
    else if (key > root->key)
        root->right = deleteBST(root->right, key);
    else {
        //�����Ϸ��� Ű�� ���� ���� ���� ���
        if ((root->left == NULL) || (root->right == NULL)) {
            //�ϳ��� �ڽ� ��常 �ְų� �ڽ��� ���� ���
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else { //�� �ڽ� ��尡 �ִ� ���
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteBST(root->right, temp->key);
        }
    }

    return root;
}

//Ž�� �Լ�
void search(Node* root, int key) {
    Node* current = root;
    while (current) {
        if (key == current->key) { 
            compareCount++; //�� Ƚ�� ����
            return; 
        }
        else if (key < current->key) {
            //ã������ Ű�� ���� ����� Ű���� ������ �������� �̵�
            current = current->left;
            compareCount++; //�� Ƚ�� ����
        }
        else {
            //ã������ Ű�� ���� ����� Ű���� ũ�� ���������� �̵�
            current = current->right;
            compareCount++; //�� Ƚ�� ����
        }
    }
}

//AVL Ʈ�� ���� ���� �Լ�
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int action = rand() % 3; //0: ����, 1: ����, 2: Ž�� �� ���� ����
        int key = rand() % 1000; //0���� 999������ ���� Ű ����

        if (action == 0) //����Ű ����
            *root = insertAVL(*root, key);
        else if (action == 1) //����Ű ����
            *root = deleteAVL(*root, key);
        else { //����Ű Ž��
            search(*root, key);
            searchCount++;
        }
    }
}

//���� Ž�� Ʈ�� ���� ���� �Լ�
void doBinaryBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int action = rand() % 3; //0: ����, 1: ����, 2: Ž�� �� ���� ����
        int key = rand() % 1000; //0���� 999������ ���� Ű ����

        if (action == 0) //����Ű ����
            *root = insertBST(*root, key);
        else if (action == 1) //����Ű ����
            *root = deleteBST(*root, key);
        else { //����Ű Ž��
            search(*root, key);
            searchCount++;
        }
    }
}

//Ʈ�� �޸� ���� �Լ�
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

//main �Լ�
int main(int argc, char* argv[]) {
    Node* root = NULL; //��Ʈ �ʱ�ȭ
    srand(time(NULL)); //���� �õ� ����
    float allCount = 0.0;

    //AVL Ʈ�� ���� ����
    doAVLBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    //AVL Ʈ�� �޸� ����
    freeTree(root);
    root = NULL; //��Ʈ �ʱ�ȭ
    compareCount = searchCount = 0; //ī���� �ʱ�ȭ

    //���� Ž�� Ʈ�� ���� ����
    doBinaryBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    //���� Ž�� Ʈ�� �޸� ����
    freeTree(root);
    return 0;
}
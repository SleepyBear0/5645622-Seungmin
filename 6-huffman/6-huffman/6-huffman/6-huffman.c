#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 7  //MAX_SIZE�� 7�� ����

//��� ����ü
typedef struct Node {
    char data;
    int freq;
    struct Node* left, * right;
} Node;

//�� ũ�⸦ �����ϴ� ����
int heap_size = 0;

//�� ��� �Լ�
void printHeap(Node* heap[], int size) {
    //����ϱ� ���� �ݺ����� ����
    for (int i = 0; i < size; i++) {
        printf("%d ", heap[i]->freq);
    }
    printf("\n");
}

//���ο� ��� ���� �Լ�
Node* createNode(char data, int freq) {
    Node* node = (Node*)malloc(sizeof(Node)); //�� ��忡 �޸� �Ҵ�
    node->data = data; //������ ����
    node->freq = freq; //�󵵼� ����
    node->left = node->right = NULL; //����, ������ �ڽ� ��带 NULL�� ����
    return node; //��� ��ȯ
}

//�� ��带 �����ϴ� �Լ�
Node* mergeNodes(Node* left, Node* right) {
    Node* node = createNode('$', left->freq + right->freq); //���� ��� ����(���ڰ� ���� ���γ�� $)
    node->left = left; 
    node->right = right;
    return node;
}

//�����͸� ��ȯ�ϴ� �Լ�
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

//�ּ� ������ �Ӽ��� �����ϴ� �Լ�
void minHeapify(Node* heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left]->freq < heap[smallest]->freq)
        smallest = left;

    if (right < size && heap[right]->freq < heap[smallest]->freq)
        smallest = right;

    //���� �ּҰ��� ��Ʈ�� �ƴϸ� ��ȯ�ϰ� ��������� �� ������ ������
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

//������ �ּ� ��带 �����ϴ� �Լ�
Node* extractMin(Node* heap[], int* size) {
    Node* temp = heap[0];  //���� ��Ʈ(�ּҰ�)
    heap[0] = heap[--(*size)];  //���� ������ ��Ҹ� ��Ʈ�� �̵�
    minHeapify(heap, *size, 0);  //�ּ� ���� �籸��
    return temp;
}

//���� �����ϰ� �����ϴ� �Լ�
void insertHeap(Node* heap[], Node* node, int* size) {
    (*size)++;
    int i = (*size) - 1;
    heap[i] = node;  //���ο� ��带 ���� �������� ����

    //�θ� ���� ���ϸ� �ּ� �� ������ ����
    while (i && heap[i]->freq < heap[(i - 1) / 2]->freq) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//������ Ʈ���� �����ϴ� �Լ�
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* heap[MAX_SIZE];  //��� ũ���� �迭 ����

    //���� �� ���ڸ� ����
    for (int i = 0; i < size; i++) {
        heap[i] = createNode(characters[i], frequencies[i]); //�� ��带 �����Ͽ� ���� ����
        heap_size++;
        //���� �� ���� �� ���
        for (int j = (heap_size - 1) / 2; j >= 0; j--) {
            minHeapify(heap, heap_size, j);
        }
        printHeap(heap, heap_size);  //���� �� �� ���� ���
    }

    //������ Ʈ�� ����
    while (heap_size > 1) {
        Node* left = extractMin(heap, &heap_size); //�󵵼��� ���� ���� ��� ����
        Node* right = extractMin(heap, &heap_size); //�״������� �󵵼��� ���� ��� ����

        printf("///%d + %d -> %d\n", left->freq, right->freq, left->freq + right->freq);  //���� ���� ���

        Node* top = mergeNodes(left, right);  //�� �ּ� �� ��带 ����
        insertHeap(heap, top, &heap_size); //���� ����

        printHeap(heap, heap_size);  //���� �� �� ���� ���
    }

    return extractMin(heap, &heap_size);  //���� ��Ʈ ��带 ��ȯ
}

//������ �ڵ� ��� �Լ�
void printCodes(Node* root, int arr[], int top) {
    //�������� ���� 1�� �߰�
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    //���������� ���� 0�� �߰�
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    //���� ��忡 �����ϸ� �ش� ������ ������ �ڵ� ���
    if (!root->left && !root->right) {
        printf("%c : ", root->data);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

//������ �ڵ� ���� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size); //������ Ʈ�� ����
    int arr[MAX_SIZE], top = 0;
    printCodes(root, arr, top); //���
}

// ���� �Լ�
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size); //������ �ڵ� ����
    return 0;
}

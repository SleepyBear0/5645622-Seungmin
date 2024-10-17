#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 7  //MAX_SIZE를 7로 정의

//노드 구조체
typedef struct Node {
    char data;
    int freq;
    struct Node* left, * right;
} Node;

//힙 크기를 추적하는 변수
int heap_size = 0;

//힙 출력 함수
void printHeap(Node* heap[], int size) {
    //출력하기 위한 반복문을 실행
    for (int i = 0; i < size; i++) {
        printf("%d ", heap[i]->freq);
    }
    printf("\n");
}

//새로운 노드 생성 함수
Node* createNode(char data, int freq) {
    Node* node = (Node*)malloc(sizeof(Node)); //새 노드에 메모리 할당
    node->data = data; //데이터 저장
    node->freq = freq; //빈도수 저장
    node->left = node->right = NULL; //왼쪽, 오른쪽 자식 노드를 NULL로 설정
    return node; //노드 반환
}

//두 노드를 병합하는 함수
Node* mergeNodes(Node* left, Node* right) {
    Node* node = createNode('$', left->freq + right->freq); //내부 노드 생성(문자가 없는 내부노드 $)
    node->left = left; 
    node->right = right;
    return node;
}

//포인터를 교환하는 함수
void swap(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

//최소 힙으로 속성을 유지하는 함수
void minHeapify(Node* heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left]->freq < heap[smallest]->freq)
        smallest = left;

    if (right < size && heap[right]->freq < heap[smallest]->freq)
        smallest = right;

    //만약 최소값이 루트가 아니면 교환하고 재귀적으로 힙 구조를 재정렬
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

//힙에서 최소 노드를 추출하는 함수
Node* extractMin(Node* heap[], int* size) {
    Node* temp = heap[0];  //힙의 루트(최소값)
    heap[0] = heap[--(*size)];  //힙의 마지막 요소를 루트로 이동
    minHeapify(heap, *size, 0);  //최소 힙을 재구성
    return temp;
}

//힙에 삽입하고 정렬하는 함수
void insertHeap(Node* heap[], Node* node, int* size) {
    (*size)++;
    int i = (*size) - 1;
    heap[i] = node;  //새로운 노드를 힙의 마지막에 삽입

    //부모 노드와 비교하며 최소 힙 성질을 유지
    while (i && heap[i]->freq < heap[(i - 1) / 2]->freq) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//허프만 트리를 생성하는 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* heap[MAX_SIZE];  //상수 크기의 배열 선언

    //힙에 각 문자를 삽입
    for (int i = 0; i < size; i++) {
        heap[i] = createNode(characters[i], frequencies[i]); //새 노드를 생성하여 힙에 삽입
        heap_size++;
        //삽입 후 정렬 및 출력
        for (int j = (heap_size - 1) / 2; j >= 0; j--) {
            minHeapify(heap, heap_size, j);
        }
        printHeap(heap, heap_size);  //삽입 후 힙 상태 출력
    }

    //허프만 트리 구성
    while (heap_size > 1) {
        Node* left = extractMin(heap, &heap_size); //빈도수가 가장 작은 노드 추출
        Node* right = extractMin(heap, &heap_size); //그다음으로 빈도수가 작은 노드 추출

        printf("///%d + %d -> %d\n", left->freq, right->freq, left->freq + right->freq);  //병합 과정 출력

        Node* top = mergeNodes(left, right);  //두 최소 빈도 노드를 병합
        insertHeap(heap, top, &heap_size); //힙에 삽입

        printHeap(heap, heap_size);  //병합 후 힙 상태 출력
    }

    return extractMin(heap, &heap_size);  //최종 루트 노드를 반환
}

//허프만 코드 출력 함수
void printCodes(Node* root, int arr[], int top) {
    //왼쪽으로 가면 1을 추가
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    //오른쪽으로 가면 0을 추가
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    //리프 노드에 도달하면 해당 문자의 허프만 코드 출력
    if (!root->left && !root->right) {
        printf("%c : ", root->data);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

//허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size); //허프만 트리 생성
    int arr[MAX_SIZE], top = 0;
    printCodes(root, arr, top); //출력
}

// 메인 함수
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size); //허프만 코드 생성
    return 0;
}

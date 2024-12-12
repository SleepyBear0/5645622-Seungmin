#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//노드 구조체 정의
typedef struct Node {
    int key;
    struct Node* left; //왼쪽 자식 노드
    struct Node* right; //오른쪽 자식 노드
    int height; // AVL 트리를 위한 높이 정보
} Node;

//전역 변수 초기화
int compareCount = 0; //탐색 시 비교 횟수
int searchCount = 0;  //탐색 횟수

//두 숫자 중 더 큰 값을 반환하는 함수
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

//노드의 높이 반환하는 함수
int getHeight(Node* node) {
    return node ? node->height : 0;
}

//오른쪽으로 회전하는 함수
Node* rightRotate(Node* y) {
    Node* x = y->left; //y의 왼쪽 자식을 x로 설정
    Node* T2 = x->right; //x의 오른쪽 자식을 T2로 설정

    //회전
    x->right = y;
    y->left = T2;

    //높이
    y->height = maxValue(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maxValue(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

//왼쪽으로 회전하는 함수
Node* leftRotate(Node* x) {
    Node* y = x->right; //x의 오른쪽 자식을 y로 설정
    Node* T2 = y->left; //y의 왼쪽 자식을 T2로 설정

    //회전
    y->left = x;
    x->right = T2;

    //높이
    x->height = maxValue(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maxValue(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

//균형 계산 함수
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

//트리에서 최소값 노드 찾기
Node* getMinValueNode(Node* node) {
    Node* current = node;

    //가장 왼쪽 노드 탐색
    while (current->left != NULL)
        current = current->left;
    return current;
}

//AVL 트리에 노드 삽입하는 함수
Node* insertAVL(Node* node, int key) {
    //이진 탐색 트리 삽입
    if (node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1; //새 노드 높이는 1
        return newNode;
    }

    if (key < node->key) {
        node->left = insertAVL(node->left, key); //왼쪽 서브트리에 삽입
    }
    else if (key > node->key) {
        node->right = insertAVL(node->right, key); //오른쪽 서브트리에 삽입
    }
    else {
        return node; //중복 키는 삽입하지 않음
    }

    //높이
    node->height = 1 + maxValue(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    //불균형 해결
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

//AVL 트리에서 노드 삭제하는 함수
Node* deleteAVL(Node* root, int key) {
    //이진 탐색 트리 삭제
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteAVL(root->left, key);
    else if (key > root->key)
        root->right = deleteAVL(root->right, key);
    else {
        //노드 삭제
        if ((root->left == NULL) || (root->right == NULL)) { //자식 노드가 한개
            Node* temp = root->left ? root->left : root->right; //그 자식노드를 temp가 가리킴
            if (temp == NULL) { //자식 노드가 없음
                temp = root; //메모리 해제
                root = NULL; //리턴
            }
            else { //자식 노드가 하나 있음
                *root = *temp; //하나 있는 자식을 부모로 대치함
            }
            free(temp);
        }
        else {
            //오른쪽 서브트리에서 최소값 노드 찾기
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    //높이
    root->height = 1 + maxValue(getHeight(root->left), getHeight(root->right));
    
    //균형인수
    int balance = getBalance(root);

    //균형 유지 회전 수행
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

//이진 탐색 트리 삽입 함수
Node* insertBST(Node* root, int key) {
    if (root == NULL) {
        //트리가 비어 있으면 새로운 노드 생성
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key; //키설정
        newNode->left = newNode->right = NULL; //자식노드는 NULL
        return newNode;
    }

    //삽입하려는 키가 현재 노드보다 작으면 왼쪽 서브트리에 크면 오른쪽 서브트리에 삽입
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);

    return root;
}

//이진 탐색 트리 삭제 함수
Node* deleteBST(Node* root, int key) {
    if (root == NULL) return root; //트로가 비어 있으면 NULL

    //삭제하려는 키가 현재 노드보다 작으면 왼쪽 서브트리에서 크면 오른쪽 서브트리에서 삭제
    if (key < root->key)
        root->left = deleteBST(root->left, key);
    else if (key > root->key)
        root->right = deleteBST(root->right, key);
    else {
        //삭제하려는 키가 현재 노드와 같을 경우
        if ((root->left == NULL) || (root->right == NULL)) {
            //하나의 자식 노드만 있거나 자식이 없는 경우
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
        else { //두 자식 노드가 있는 경우
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteBST(root->right, temp->key);
        }
    }

    return root;
}

//탐색 함수
void search(Node* root, int key) {
    Node* current = root;
    while (current) {
        if (key == current->key) { 
            compareCount++; //비교 횟수 증가
            return; 
        }
        else if (key < current->key) {
            //찾으려는 키가 현재 노드의 키보다 작으면 왼쪽으로 이동
            current = current->left;
            compareCount++; //비교 횟수 증가
        }
        else {
            //찾으려는 키가 현재 노드의 키보다 크면 오른쪽으로 이동
            current = current->right;
            compareCount++; //비교 횟수 증가
        }
    }
}

//AVL 트리 실험 수행 함수
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int action = rand() % 3; //0: 삽입, 1: 삭제, 2: 탐색 중 랜덤 선택
        int key = rand() % 1000; //0부터 999까지의 랜덤 키 생성

        if (action == 0) //랜덤키 삽입
            *root = insertAVL(*root, key);
        else if (action == 1) //랜덤키 삭제
            *root = deleteAVL(*root, key);
        else { //랜덤키 탐색
            search(*root, key);
            searchCount++;
        }
    }
}

//이진 탐색 트리 실험 수행 함수
void doBinaryBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int action = rand() % 3; //0: 삽입, 1: 삭제, 2: 탐색 중 랜덤 선택
        int key = rand() % 1000; //0부터 999까지의 랜덤 키 생성

        if (action == 0) //랜덤키 삽입
            *root = insertBST(*root, key);
        else if (action == 1) //랜덤키 삭제
            *root = deleteBST(*root, key);
        else { //랜덤키 탐색
            search(*root, key);
            searchCount++;
        }
    }
}

//트리 메모리 해제 함수
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

//main 함수
int main(int argc, char* argv[]) {
    Node* root = NULL; //루트 초기화
    srand(time(NULL)); //랜덤 시드 설정
    float allCount = 0.0;

    //AVL 트리 실험 수행
    doAVLBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    //AVL 트리 메모리 해제
    freeTree(root);
    root = NULL; //루트 초기화
    compareCount = searchCount = 0; //카운터 초기화

    //이진 탐색 트리 실험 수행
    doBinaryBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    //이진 탐색 트리 메모리 해제
    freeTree(root);
    return 0;
}
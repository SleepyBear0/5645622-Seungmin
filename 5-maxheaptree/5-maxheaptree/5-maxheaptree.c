#include <stdio.h>
#include <stdlib.h>

//트리의 노드 구조체
typedef struct TreeNode {
    int data; //노드에 저장된 데이터
    struct TreeNode* left; //왼쪽 자식 노드
    struct TreeNode* right;//오른쪽 자식 노드
} TreeNode;

int moveCount = 0; //노드 이동 횟수

//새로운 노드를 생성하는 함수
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode)); //동적메모리할당
    newNode->data = data; //데이터 설정
    newNode->left = newNode->right = NULL; //자식 노드를 NULL로 초기화
    return newNode;
}

//현재 트리 상태를 출력하는 함수
TreeNode* currentRoot = NULL; //현재 루트를 전역 변수로 사용

//현재 트리를 레벨 순서대로 출력하는 함수
void printCurrentTree() {
    if (currentRoot == NULL) return; //트리가 비어있으면 리턴

    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); //큐 구현(큐 동적할당)
    int front = 0, rear = 0;

    queue[rear++] = currentRoot; //루트 노드를 큐에 추가

    while (front < rear) {
        TreeNode* current = queue[front++]; //큐에서 노드 꺼내기
        printf("%d ", current->data); //현재 노드 출력

        //왼쪽과 오른쪽 자식 노드 큐에 추가
        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }

    printf("\n"); //출력 후 줄 바꿈
    free(queue); //큐 메모리 해제
}
//히프를 정렬하는 함수 (노드가 최대 히프 조건을 만족하도록)
void heapify(TreeNode* node) {
    if (node == NULL) return;

    TreeNode* current = node; //삽입된 노드를 기준으로 시작
    TreeNode* parent = NULL; //부모 노드를 추적하기 위한 포인터

    //삽입된 노드 부모와 비교하면서 히프 정렬
    while (current != currentRoot) {
        parent = currentRoot; //부모 노드 찾기
        TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); //부모 찾기를 하기 위한 큐
        int front = 0, rear = 0;

        queue[rear++] = parent;

        //부모 노드를 찾기 위한 탐색
        while (front < rear) {
            TreeNode* temp = queue[front++];
            if (temp->left == current || temp->right == current) {
                parent = temp; //부모 노드 발견
                break;
            }
            if (temp->left) queue[rear++] = temp->left;
            if (temp->right) queue[rear++] = temp->right;
        }

        free(queue); //큐 메모리 해제

        //부모가 존재하고 현재 노드(자식)가 부모보다 크면 교환
        if (parent && current->data > parent->data) {
            int temp = current->data;
            current->data = parent->data;
            parent->data = temp;

            moveCount++; //이동 횟수 증가

            //트리 상태 출력 (교환 후)
            printCurrentTree();

            //현재 노드를 부모로 업데이트하여 반복
            current = parent;
        }
        else {
            break; //더 이상 교환할 필요 없음
        }
    }
}

//삭제 후 히프를 재배열하는 함수 (삭제된 루트 노드 기준으로)
void heapify_del(TreeNode* node) {
    if (node == NULL) return;

    TreeNode* current = node; //루트 노드로부터 시작

    while (1) {
        TreeNode* largest = current;
        TreeNode* leftChild = current->left; //왼쪽 자식
        TreeNode* rightChild = current->right; //오른쪽 자식

        //왼쪽 자식과 비교하여 큰 값 찾기
        if (leftChild && leftChild->data > largest->data) {
            largest = leftChild;
        }

        //오른쪽 자식과 비교하여 큰 값 찾기
        if (rightChild && rightChild->data > largest->data) {
            largest = rightChild;
        }

        //만약 현재 노드가 가장 크지 않으면 교환
        if (largest != current) {
            //현재 노드와 가장 큰 자식 노드 교환
            int temp = current->data;
            current->data = largest->data;
            largest->data = temp;

            moveCount++; // 이동 횟수 증가

            //트리 상태 출력 (교환 후)
            printCurrentTree();

            //교환 후 현재 노드를 가장 큰 자식으로 업데이트 후 반복
            current = largest;
        }
        else {
            break; //더 이상 교환할 필요 없음
        }
    }
}

//최대 히프 트리에 노드를 삽입하는 함수
TreeNode* insertMaxHeap(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data); //루트가 없으면 새로운 노드를 루트로 설정
    }

    //새로운 노드를 생성
    TreeNode* newNode = createNode(data);

    //큐를 사용하여 삽입할 위치를 찾기
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*)); //큐 동적 할당
    int front = 0, rear = 0;

    queue[rear++] = root; //루트 노드를 큐에 추가

    while (front < rear) {
        TreeNode* current = queue[front++]; //큐에서 노드 꺼내기

        //왼쪽 자식이 비어 있으면 여기에 새로운 노드를 삽입
        if (current->left == NULL) {
            current->left = newNode;
            break;
        }
        else {
            queue[rear++] = current->left; //왼쪽 자식 노드를 큐에 추가
        }

        //오른쪽 자식이 비어 있으면 여기에 새로운 노드를 삽입
        if (current->right == NULL) {
            current->right = newNode;
            break;
        }
        else {
            queue[rear++] = current->right; //오른쪽 자식 노드를 큐에 추가
        }
    }

    free(queue); //메모리 해제

    printCurrentTree(); //히프 정렬 수행 전 트리 출력

    //히프 정렬 수행 (새로운 노드를 삽입한 후)
    heapify(newNode); //새로운 노드를 기준으로 힙을 조정

    return root;
}

//최대 히프에서 루트 노드를 삭제하는 함수
TreeNode* deleteRoot(TreeNode* root) {
    if (root == NULL) return NULL;

    //루트 노드를 저장하고 마지막 노드를 찾기 위해 탐색
    TreeNode** queue = (TreeNode**)malloc(100 * sizeof(TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    TreeNode* lastNode = NULL;
    TreeNode* parent = NULL;

    while (front < rear) {
        lastNode = queue[front++]; //큐에서 마지막 노드 꺼내기

        if (lastNode->left) {
            queue[rear++] = lastNode->left; //왼쪽 자식 노드를 큐에 추가
        }
        if (lastNode->right) {
            queue[rear++] = lastNode->right; //오른쪽 자식 노드를 큐에 추가
        }
    }

    //루트 노드의 데이터에 마지막 노드의 데이터를 복사
    root->data = lastNode->data;

    //마지막 노드를 삭제
    front = 0; rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        parent = queue[front++];

        if (parent->left == lastNode) {
            parent->left = NULL; //왼쪽 자식 삭제
            break;
        }
        else if (parent->right == lastNode) {
            parent->right = NULL; //오른쪽 자식 삭제
            break;
        }

        if (parent->left) queue[rear++] = parent->left; //왼쪽 자식 큐에 추가
        if (parent->right) queue[rear++] = parent->right; //오른쪽 자식 큐에 추가
    }

    free(lastNode); //마지막 노드 메모리 해제

    printCurrentTree(); //히프 정렬 수행 전 트리 출력

    moveCount = 1; //이동 횟수 초기화

    heapify_del(root); //새로운 루트를 기준으로 히프 정렬

    free(queue); //메모리 해제

    return root;
}

// 트리를 레벨별로 출력하는 함수
void printLevelOrder(TreeNode* root, int level) {
    if (root == NULL) return; //노드가 NULL이면 리턴

    if (level == 1)
        printf("%d ", root->data); //현재 레벨이 1이면 현재 노드의 데이터 출력
    else {
        //재귀적으로 왼쪽과 오른쪽 자식을 탐색하여 레벨에 맞는 노드 출력
        printLevelOrder(root->left, level - 1);
        printLevelOrder(root->right, level - 1);
    }
}

// 트리의 높이를 계산하는 함수
int height(TreeNode* root) {
    if (root == NULL) return 0; //노드가 NULL이면 0리턴(높이가 0)
    //왼쪽과 오른쪽 서브트리의 높이를 재귀적으로 계산한 후, 더 큰 값에 1을 더해 반환
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

//트리의 레벨별 순회 출력 함수
void levelOrder(TreeNode* root) {
    int i;
    int h = height(root); //트리의 높이
    //레벨별 노드 출력
    for (i = 1; i <= h; i++) {
        printf("[%d] ", i);
        printLevelOrder(root, i);
        printf("\n");
    }
    printf("\n");
}

//유저 인터페이스 함수
void runUserInterface(TreeNode* root) {
    char command; //사용자가 입력할 명령어 변수
    int data; //삽입할 노드 데이터 변수

    currentRoot = root; //전역변수 currentRoot를 root로 초기화

    //c를 입력하기 전까지 무한반복
    while (1) {
        printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
        printf("| i\t : 노드 추가\t|\n");
        printf("| d\t : 노드 삭제\t|\n");
        printf("| p\t : 레벨별 출력\t|\n");
        printf("| c\t : 종료\t\t|\n");
        printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");

        printf("메뉴 입력: ");
        scanf_s(" %c", &command); //명령어 받기

        switch (command) {
        case 'i': //i를 입력했을 경우(삽입)
            printf("추가할 값 입력: ");
            scanf_s("%d", &data);
            moveCount = 0; //이동 횟수 초기화
            root = insertMaxHeap(root, data); //입력된 데이터 히프에 삽입
            printf("노드가 이동된 횟수: %d\n\n", moveCount); //이동 횟수 출력
            break;
        case 'd': //d를 입력했을 경우(삭제)
            moveCount = 0; //이동 횟수 초기화
            root = deleteRoot(root); //삭제 함수 호출
            printf("노드가 이동된 횟수: %d\n\n", moveCount);
            break;
        case 'p': //p를 입력했을 경우(출력)
            printf("트리 레벨별 출력\n");
            levelOrder(root); //levelOrder 호출
            break;
        case 'c': //c를 입력했을 경우(종료)
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 명령입니다. 다시 입력하세요.\n"); //잘못된 명령을 쳤을 경우
        }
    }
}

// 초기 데이터를 이용하여 최대 히프 트리 생성하는 함수
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = createNode(90); //루트 노드 생성

    //자식 노드 생성
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
    //pdf출력결과와 트리의 데이터 수가 다름! => pdf 트리 기준으로 데이터 입력!!
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]); //배열의 크기

    //트리 생성
    TreeNode* root = generateMaxHeapTree(inputData, size);

    //유저 인터페이스 실행
    runUserInterface(root);

    //메모리 해제
    free(root);
    return 0;
}
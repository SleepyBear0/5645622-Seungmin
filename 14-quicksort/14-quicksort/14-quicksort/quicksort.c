#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0; //비교 횟수
int moveCount = 0; //이동 횟수
int totalComparisons = 0; //총 비교 횟수
int totalMoveCount = 0; //총 이동 횟수
int isFirst = 0; //첫 번째 실행 여부

//랜덤 배열 생성 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 사이의 랜덤 값 생성
    }
}

//배열 출력 함수
void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//두 값을 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    moveCount++; //temp에 값을 저장, movecount 1증가
    *a = *b;
    moveCount++; //temp 값을 a에 넣는 작업, movecount 1증가
    *b = temp;
    moveCount++; //temp 값을 b에 넣는 작업, movecount 1증가
}

//배열을 분할하는 함수
int partition(int* array, int low, int high) {
    int pivot = array[high]; //피벗으로 배열의 마지막 요소를 선택
    moveCount++; //피벗을 설정하는 작업을 이동으로 계산
    int i = low - 1; //피벗보다 작은 요소의 인덱스

    for (int j = low; j <= high - 1; j++) {
        comparisonCount++; //각 비교를 비교 횟수로 계산
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]); //요소 교환
        }
    }
    swap(&array[i + 1], &array[high]); //피벗을 올바른 위치로 이동
    return i + 1;
}

//반복적 방법으로 구현한 퀵 정렬 함수
void doQuickSort(int* array, int low, int high) {
    int stack[SIZE]; //스택 배열 선언
    int top = -1;    //스택의 최상위 인덱스 초기화

    //초기 low와 high를 스택에 push
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        //스택에서 high와 low를 pop
        high = stack[top--];
        low = stack[top--];

        int pivotIndex = partition(array, low, high); //분할 실행

        //첫 번째 실행 중 중간 상태를 출력 (40~60의 위치에 있는 값만 출력)
        if (isFirst == 0 && pivotIndex >= 40 && pivotIndex <= 60) {
            for (int i = 40; i <= 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }

        //왼쪽 부분 배열을 스택에 push
        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        //오른쪽 부분 배열을 스택에 push
        if (pivotIndex + 1 < high) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); //랜덤 데이터 생성
        comparisonCount = 0; //비교 횟수 초기화
        moveCount = 0; //이동 횟수 초기화

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); //정렬 실행 및 중간 과정 출력
            printf("Result\n");
            printArray(array, SIZE); //정렬 결과 출력
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1); //정렬 실행
        }

        totalComparisons += comparisonCount; //총 비교 횟수 누적
        totalMoveCount += moveCount; //총 이동 횟수 누적
    }

    //평균 비교 및 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}

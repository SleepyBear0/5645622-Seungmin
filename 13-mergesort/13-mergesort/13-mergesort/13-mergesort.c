#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

//전역 변수
int comparisonCount = 0; //비교 횟수
int moveCount = 0;       //이동 횟수

//배열 출력 함수
void printArray(int array[], int start, int end) {
    for (int i = start; i <= end && i < SIZE; i++) {
        printf("%4d", array[i]);
    }
}

//합병 함수
void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* leftArr = (int*)malloc(n1 * sizeof(int));
    int* rightArr = (int*)malloc(n2 * sizeof(int));

    //원래 배열에서 임시 배열로 복사하는 과정
    for (int i = 0; i < n1; i++) {
        leftArr[i] = array[left + i];
        moveCount++;
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = array[mid + 1 + j];
        moveCount++;
    }

    //병합 과정
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisonCount++;
        if (leftArr[i] <= rightArr[j]) {
            array[k] = leftArr[i];
            i++;
        }
        else {
            array[k] = rightArr[j];
            j++;
        }
        moveCount++;
        k++;
    }

    //남은 요소를 원래 배열로 복사
    while (i < n1) {
        array[k] = leftArr[i];
        i++;
        k++;
        moveCount++;
    }
    while (j < n2) {
        array[k] = rightArr[j];
        j++;
        k++;
        moveCount++;
    }

    free(leftArr);
    free(rightArr);
}

//반복적 합병 정렬 함수
void iterativeMergeSort(int array[], int n) {
    //부분 배열의 크기를 1에서 시작해 반복적으로 병합
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        //부분 배열의 시작 위치를 순차적으로 처리
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1; //중간 인덱스
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? left_start + 2 * curr_size - 1 : n - 1; //오른쪽 끝 인덱스

            merge(array, left_start, mid, right_end); //두 하위 배열 병합
        }
    }
}

//랜덤 배열 생성 함수
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

//합병 정렬 실행 함수
void doMergeSort(int array[], int size) {
    int iteration = 1; //병합 횟수 카운트

    for (int curr_size = 1; curr_size <= size - 1; curr_size *= 2) {
        for (int left_start = 0; left_start < size - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1; //중간 인덱스
            int right_end = (left_start + 2 * curr_size - 1 < size - 1) ? left_start + 2 * curr_size - 1 : size - 1; //오른쪽 끝 인덱스

            merge(array, left_start, mid, right_end); //두 하위 배열 병합

            //출력 조건: 10번에 1번씩 출력
            if (iteration % 10 == 0) {
                printArray(array, 0, 9); //첫 10개의 요소 출력
                printf(" |");

                int midPos = size / 2 - 1; //중간 지점에서 10개의 요소 출력
                printArray(array, midPos, midPos + 10);
                printf("\n");
            }
            iteration++;
        }
    }
}

int main() {
    int array[SIZE];
    srand((unsigned)time(NULL));

    double totalComparisons = 0;
    double totalMoves = 0;

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); //랜덤 배열 생성
        comparisonCount = 0; //비교 횟수 초기화
        moveCount = 0; //이동 횟수 초기화

        if (i == 0) { //첫 번째 실행 시 상세 출력
            printf("Merge Sort Run\n");
            doMergeSort(array, SIZE); //합병 정렬 실행

            printf("\nResult:\n");
            printArray(array, 0, SIZE - 1); //정렬된 전체 배열 출력
        }
        else {
            iterativeMergeSort(array, SIZE);
        }

        totalComparisons += comparisonCount; //비교 횟수 누적
        totalMoves += moveCount; //이동 횟수 누적
    }

    //평균 비교 및 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}

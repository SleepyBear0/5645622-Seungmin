#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

//랜덤 숫자 생성 함수
void generateRandomNumbers(int array[]) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; //0 ~ 999 사이의 랜덤 숫자
    }
}

//배열 복사 함수
void copyArray(int dest[], int src[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        dest[i] = src[i];
    }
}

//배열 출력 함수
void printArray(int array[], int size, int full) {
    for (int i = 0; i < size && (full || i < 20); i++) {
        printf("%d ", array[i]); //배열 요소 출력
    }
    if (!full && size > 20) {
        printf("...");
    }
    printf("\n\n");
}

//쉘 정렬 함수
void doShellSort(int array[], int divider, int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE]; //임시배열
    copyArray(tempArray, array); //원본 배열 복사
    int size = ARRAY_SIZE;
    *comparisonCount = 0; //비교 횟수 초기화
    *moveCount = 0; //이동 횟수 초기화

    int gap = size / divider; //초기 간격 설정

    while (gap > 0) { //간격이 0이 될 때까지 반복
        printf("Sorting with gap = %d:\n", gap);
        printArray(tempArray, ARRAY_SIZE, 0); //배열 상태 출력

        //간격만큼 떨어진 요소들 비교 및 정렬
        for (int i = gap; i < size; i++) {
            int temp = tempArray[i];
            (*moveCount)++; 
            int j;
            for (j = i; j >= gap && (++(*comparisonCount)) && tempArray[j - gap] > temp; j -= gap) {
                tempArray[j] = tempArray[j - gap];
                (*moveCount)++;
            }
            tempArray[j] = temp;
            (*moveCount)++;
        }
        gap /= divider; //간격 줄이기
    }

    printf("Sorted shellArray (gap=%d):\n", divider); //최정 정렬된 배열 출력
    printArray(tempArray, ARRAY_SIZE, 1); //전체 배열 출력
}

//삽입 정렬 함수
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE]; //임시배열
    copyArray(tempArray, array); //원본 배열 복사
    int size = ARRAY_SIZE;
    *comparisonCount = 0; //비교 횟수 초기화
    *moveCount = 0; //이동 횟수 초기화

    for (int i = 1; i < size; i++) {
        int temp = tempArray[i];
        (*moveCount)++;
        int j;
        for (j = i - 1; j >= 0 && (++(*comparisonCount)) && tempArray[j] > temp; j--) {
            tempArray[j + 1] = tempArray[j];
            (*moveCount)++;
        }
        tempArray[j + 1] = temp; //값 저장
        (*moveCount)++;
    }

    printf("Sorted insertionArray:\n");
    printArray(tempArray, ARRAY_SIZE, 1); //최정 정렬된 배열 출력
}

int main() {
    int array[ARRAY_SIZE]; //사용할 배열
    int comparisonCount, moveCount;

    generateRandomNumbers(array); //랜덤 수 생성

    //Shell Sort (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    //Shell Sort (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    //Insertion Sort - 보너스
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}

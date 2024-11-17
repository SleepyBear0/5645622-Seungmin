#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

//랜덤 숫자 생성 함수
void generateRandomData(int data[]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; //0~999 사이의 랜덤 숫자
    }
}

//선택 정렬 함수
void doSelectionSort(int data[]) {
    int temp, minIndex;
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = data[i]; //원본 데이터 복사
    }

    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        minIndex = i;
        //최소값 찾기
        for (int j = i + 1; j < SIZE; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        //최소값과 현재 위치의 값 교환
        temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;

        //정렬 과정 출력
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) {
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", array[k]);
            }
            printf("\n\n");
        }
    }
}

//삽입 정렬 함수
void doInsertionSort(int data[]) {
    int totalComparisons = 0; //전체 비교 횟수
    int array[SIZE];
    int comparisons, temp;

    for (int trial = 0; trial < TRIALS; trial++) {
        for (int i = 0; i < SIZE; i++) {
            array[i] = data[i]; //원본 데이터 복사
        }

        //현재 시도의 비교 횟수 초기화
        comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            temp = array[i];
            int j = i - 1;
            //삽입 위치를 찾기 위해 뒤로 이동
            while (j >= 0 && array[j] > temp) {
                array[j + 1] = array[j];
                j--;
                comparisons++; //비교 횟수 증가
            }
            array[j + 1] = temp;
            comparisons++; //비교 횟수 증가
        }
        totalComparisons += comparisons; //총 비교 횟수에 더하기
    }
    //평균 비교 횟수 출력
    printf("\nInsertion Sort Compare Average: %.f\n", totalComparisons / (float)TRIALS);

    //정렬된 결과 출력
    printf("Insertion Sort Result: \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//버블 정렬 함수
void doBubbleSort(int data[]) {
    int totalMoves = 0; //전체 이동 횟수
    int array[SIZE];
    int moves, temp;

    for (int trial = 0; trial < TRIALS; trial++) {
        for (int i = 0; i < SIZE; i++) {
            array[i] = data[i]; //원본 데이터 복사
        }

        moves = 0; //현재 시도의 이동 횟수 초기화
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - 1 - i; j++) {
                if (array[j] > array[j + 1]) {
                    //값 교환
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    moves += 3;
                }
            }
        }
        totalMoves += moves; //총 이동 횟수에 더함
    }
    //평균 이동 횟수 출력
    printf("\n\nBubble Sort Move Average: %.f\n", totalMoves / (float)TRIALS);

    //정렬된 결과 출력
    printf("Bubble Sort Result: \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
}

int main() {
    int randomData[SIZE]; //랜덤 데이터를 저장할 배열
    generateRandomData(randomData); //랜덤 숫자 생성

    doSelectionSort(randomData); //선택 정렬
    doInsertionSort(randomData); //삽입 정렬
    doBubbleSort(randomData); //버블 정렬

    return 0;
}

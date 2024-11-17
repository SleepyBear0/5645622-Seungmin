#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

//���� ���� ���� �Լ�
void generateRandomNumbers(int array[]) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; //0 ~ 999 ������ ���� ����
    }
}

//�迭 ���� �Լ�
void copyArray(int dest[], int src[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        dest[i] = src[i];
    }
}

//�迭 ��� �Լ�
void printArray(int array[], int size, int full) {
    for (int i = 0; i < size && (full || i < 20); i++) {
        printf("%d ", array[i]); //�迭 ��� ���
    }
    if (!full && size > 20) {
        printf("...");
    }
    printf("\n\n");
}

//�� ���� �Լ�
void doShellSort(int array[], int divider, int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE]; //�ӽù迭
    copyArray(tempArray, array); //���� �迭 ����
    int size = ARRAY_SIZE;
    *comparisonCount = 0; //�� Ƚ�� �ʱ�ȭ
    *moveCount = 0; //�̵� Ƚ�� �ʱ�ȭ

    int gap = size / divider; //�ʱ� ���� ����

    while (gap > 0) { //������ 0�� �� ������ �ݺ�
        printf("Sorting with gap = %d:\n", gap);
        printArray(tempArray, ARRAY_SIZE, 0); //�迭 ���� ���

        //���ݸ�ŭ ������ ��ҵ� �� �� ����
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
        gap /= divider; //���� ���̱�
    }

    printf("Sorted shellArray (gap=%d):\n", divider); //���� ���ĵ� �迭 ���
    printArray(tempArray, ARRAY_SIZE, 1); //��ü �迭 ���
}

//���� ���� �Լ�
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE]; //�ӽù迭
    copyArray(tempArray, array); //���� �迭 ����
    int size = ARRAY_SIZE;
    *comparisonCount = 0; //�� Ƚ�� �ʱ�ȭ
    *moveCount = 0; //�̵� Ƚ�� �ʱ�ȭ

    for (int i = 1; i < size; i++) {
        int temp = tempArray[i];
        (*moveCount)++;
        int j;
        for (j = i - 1; j >= 0 && (++(*comparisonCount)) && tempArray[j] > temp; j--) {
            tempArray[j + 1] = tempArray[j];
            (*moveCount)++;
        }
        tempArray[j + 1] = temp; //�� ����
        (*moveCount)++;
    }

    printf("Sorted insertionArray:\n");
    printArray(tempArray, ARRAY_SIZE, 1); //���� ���ĵ� �迭 ���
}

int main() {
    int array[ARRAY_SIZE]; //����� �迭
    int comparisonCount, moveCount;

    generateRandomNumbers(array); //���� �� ����

    //Shell Sort (n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    //Shell Sort (n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    //Insertion Sort - ���ʽ�
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}

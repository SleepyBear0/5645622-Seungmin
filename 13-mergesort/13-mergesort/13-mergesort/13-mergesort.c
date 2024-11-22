#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

//���� ����
int comparisonCount = 0; //�� Ƚ��
int moveCount = 0;       //�̵� Ƚ��

//�迭 ��� �Լ�
void printArray(int array[], int start, int end) {
    for (int i = start; i <= end && i < SIZE; i++) {
        printf("%4d", array[i]);
    }
}

//�պ� �Լ�
void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* leftArr = (int*)malloc(n1 * sizeof(int));
    int* rightArr = (int*)malloc(n2 * sizeof(int));

    //���� �迭���� �ӽ� �迭�� �����ϴ� ����
    for (int i = 0; i < n1; i++) {
        leftArr[i] = array[left + i];
        moveCount++;
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = array[mid + 1 + j];
        moveCount++;
    }

    //���� ����
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

    //���� ��Ҹ� ���� �迭�� ����
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

//�ݺ��� �պ� ���� �Լ�
void iterativeMergeSort(int array[], int n) {
    //�κ� �迭�� ũ�⸦ 1���� ������ �ݺ������� ����
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        //�κ� �迭�� ���� ��ġ�� ���������� ó��
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1; //�߰� �ε���
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? left_start + 2 * curr_size - 1 : n - 1; //������ �� �ε���

            merge(array, left_start, mid, right_end); //�� ���� �迭 ����
        }
    }
}

//���� �迭 ���� �Լ�
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

//�պ� ���� ���� �Լ�
void doMergeSort(int array[], int size) {
    int iteration = 1; //���� Ƚ�� ī��Ʈ

    for (int curr_size = 1; curr_size <= size - 1; curr_size *= 2) {
        for (int left_start = 0; left_start < size - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1; //�߰� �ε���
            int right_end = (left_start + 2 * curr_size - 1 < size - 1) ? left_start + 2 * curr_size - 1 : size - 1; //������ �� �ε���

            merge(array, left_start, mid, right_end); //�� ���� �迭 ����

            //��� ����: 10���� 1���� ���
            if (iteration % 10 == 0) {
                printArray(array, 0, 9); //ù 10���� ��� ���
                printf(" |");

                int midPos = size / 2 - 1; //�߰� �������� 10���� ��� ���
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
        generateRandomArray(array); //���� �迭 ����
        comparisonCount = 0; //�� Ƚ�� �ʱ�ȭ
        moveCount = 0; //�̵� Ƚ�� �ʱ�ȭ

        if (i == 0) { //ù ��° ���� �� �� ���
            printf("Merge Sort Run\n");
            doMergeSort(array, SIZE); //�պ� ���� ����

            printf("\nResult:\n");
            printArray(array, 0, SIZE - 1); //���ĵ� ��ü �迭 ���
        }
        else {
            iterativeMergeSort(array, SIZE);
        }

        totalComparisons += comparisonCount; //�� Ƚ�� ����
        totalMoves += moveCount; //�̵� Ƚ�� ����
    }

    //��� �� �� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}

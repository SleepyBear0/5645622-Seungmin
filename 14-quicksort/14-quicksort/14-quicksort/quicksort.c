#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0; //�� Ƚ��
int moveCount = 0; //�̵� Ƚ��
int totalComparisons = 0; //�� �� Ƚ��
int totalMoveCount = 0; //�� �̵� Ƚ��
int isFirst = 0; //ù ��° ���� ����

//���� �迭 ���� �Լ�
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 ������ ���� �� ����
    }
}

//�迭 ��� �Լ�
void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//�� ���� ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    moveCount++; //temp�� ���� ����, movecount 1����
    *a = *b;
    moveCount++; //temp ���� a�� �ִ� �۾�, movecount 1����
    *b = temp;
    moveCount++; //temp ���� b�� �ִ� �۾�, movecount 1����
}

//�迭�� �����ϴ� �Լ�
int partition(int* array, int low, int high) {
    int pivot = array[high]; //�ǹ����� �迭�� ������ ��Ҹ� ����
    moveCount++; //�ǹ��� �����ϴ� �۾��� �̵����� ���
    int i = low - 1; //�ǹ����� ���� ����� �ε���

    for (int j = low; j <= high - 1; j++) {
        comparisonCount++; //�� �񱳸� �� Ƚ���� ���
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]); //��� ��ȯ
        }
    }
    swap(&array[i + 1], &array[high]); //�ǹ��� �ùٸ� ��ġ�� �̵�
    return i + 1;
}

//�ݺ��� ������� ������ �� ���� �Լ�
void doQuickSort(int* array, int low, int high) {
    int stack[SIZE]; //���� �迭 ����
    int top = -1;    //������ �ֻ��� �ε��� �ʱ�ȭ

    //�ʱ� low�� high�� ���ÿ� push
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        //���ÿ��� high�� low�� pop
        high = stack[top--];
        low = stack[top--];

        int pivotIndex = partition(array, low, high); //���� ����

        //ù ��° ���� �� �߰� ���¸� ��� (40~60�� ��ġ�� �ִ� ���� ���)
        if (isFirst == 0 && pivotIndex >= 40 && pivotIndex <= 60) {
            for (int i = 40; i <= 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
        }

        //���� �κ� �迭�� ���ÿ� push
        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        //������ �κ� �迭�� ���ÿ� push
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
        generateRandomArray(array); //���� ������ ����
        comparisonCount = 0; //�� Ƚ�� �ʱ�ȭ
        moveCount = 0; //�̵� Ƚ�� �ʱ�ȭ

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); //���� ���� �� �߰� ���� ���
            printf("Result\n");
            printArray(array, SIZE); //���� ��� ���
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1); //���� ����
        }

        totalComparisons += comparisonCount; //�� �� Ƚ�� ����
        totalMoveCount += moveCount; //�� �̵� Ƚ�� ����
    }

    //��� �� �� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}

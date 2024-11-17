#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define TRIALS 20

//���� ���� ���� �Լ�
void generateRandomData(int data[]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000; //0~999 ������ ���� ����
    }
}

//���� ���� �Լ�
void doSelectionSort(int data[]) {
    int temp, minIndex;
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = data[i]; //���� ������ ����
    }

    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        minIndex = i;
        //�ּҰ� ã��
        for (int j = i + 1; j < SIZE; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        //�ּҰ��� ���� ��ġ�� �� ��ȯ
        temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;

        //���� ���� ���
        if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) {
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", array[k]);
            }
            printf("\n\n");
        }
    }
}

//���� ���� �Լ�
void doInsertionSort(int data[]) {
    int totalComparisons = 0; //��ü �� Ƚ��
    int array[SIZE];
    int comparisons, temp;

    for (int trial = 0; trial < TRIALS; trial++) {
        for (int i = 0; i < SIZE; i++) {
            array[i] = data[i]; //���� ������ ����
        }

        //���� �õ��� �� Ƚ�� �ʱ�ȭ
        comparisons = 0;
        for (int i = 1; i < SIZE; i++) {
            temp = array[i];
            int j = i - 1;
            //���� ��ġ�� ã�� ���� �ڷ� �̵�
            while (j >= 0 && array[j] > temp) {
                array[j + 1] = array[j];
                j--;
                comparisons++; //�� Ƚ�� ����
            }
            array[j + 1] = temp;
            comparisons++; //�� Ƚ�� ����
        }
        totalComparisons += comparisons; //�� �� Ƚ���� ���ϱ�
    }
    //��� �� Ƚ�� ���
    printf("\nInsertion Sort Compare Average: %.f\n", totalComparisons / (float)TRIALS);

    //���ĵ� ��� ���
    printf("Insertion Sort Result: \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//���� ���� �Լ�
void doBubbleSort(int data[]) {
    int totalMoves = 0; //��ü �̵� Ƚ��
    int array[SIZE];
    int moves, temp;

    for (int trial = 0; trial < TRIALS; trial++) {
        for (int i = 0; i < SIZE; i++) {
            array[i] = data[i]; //���� ������ ����
        }

        moves = 0; //���� �õ��� �̵� Ƚ�� �ʱ�ȭ
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - 1 - i; j++) {
                if (array[j] > array[j + 1]) {
                    //�� ��ȯ
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    moves += 3;
                }
            }
        }
        totalMoves += moves; //�� �̵� Ƚ���� ����
    }
    //��� �̵� Ƚ�� ���
    printf("\n\nBubble Sort Move Average: %.f\n", totalMoves / (float)TRIALS);

    //���ĵ� ��� ���
    printf("Bubble Sort Result: \n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
}

int main() {
    int randomData[SIZE]; //���� �����͸� ������ �迭
    generateRandomData(randomData); //���� ���� ����

    doSelectionSort(randomData); //���� ����
    doInsertionSort(randomData); //���� ����
    doBubbleSort(randomData); //���� ����

    return 0;
}

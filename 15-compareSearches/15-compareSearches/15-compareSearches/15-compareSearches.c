#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

//��Ƚ���� �����ϴ� ����
int compareCount = 0;

//������ �迭 ����
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0 ~ 999 ������ ����
    }
}

//���� Ž��
int linearSearch(int* array, int target) {
    int count = 0; //�� Ƚ��
    for (int i = 0; i < SIZE; i++) {
        count++; //�� Ƚ�� ����
        if (array[i] == target) //���� ��Ұ� ��ǥ���� ������ ����
            break;
    }
    return count;
}

//��� �� Ƚ�� ��� �Լ�
double getAverageLinearSearchCompareCount(int* array) {
    double totalCount = 0; //�� �� Ƚ���� �����ϴ� ����
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; //�迭���� ������ ���� Ÿ������ ����
        totalCount += linearSearch(array, target); //���� Ž�� ���� �� �� Ƚ�� ����
    }
    return totalCount / 100.0; //��� �� Ƚ�� ��ȯ
}

//�� �����Լ�
void quickSort(int* array, int left, int right) {
    if (left >= right)
        return;
    int pivot = array[left]; //�Ǹ����� �迭�� ù��° ��� ����
    int i = left + 1;
    int j = right;

    while (i <= j) {
        //���ʿ��� �ǹ����� ū ���� ã��
        while (i <= right && array[i] <= pivot) {
            i++;
            compareCount++; //�� Ƚ�� ����
        }
        //�����ʿ��� �ǹ����� ���� ���� ã��
        while (j > left && array[j] >= pivot) {
            j--;
            compareCount++; //�� Ƚ�� ����
        }
        //�� ��ȯ
        if (i < j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[left];
    array[left] = array[j];
    array[j] = temp;

    quickSort(array, left, j - 1);
    quickSort(array, j + 1, right);
}

//�� ������ �� Ƚ�� ��� �Լ�
void getQuickSortCompareCount(int* array) {
    compareCount = 0; //�� Ƚ�� �ʱ�ȭ
    quickSort(array, 0, SIZE - 1);
}

//���� Ž���Լ�
int binarySearch(int* array, int target) {
    int left = 0, right = SIZE - 1, count = 0;
    while (left <= right) {
        count++; //�� Ƚ�� ����
        int mid = (left + right) / 2; //�߾� ����� �ε��� ���
        if (array[mid] == target) //��ǥ �� ã���� ����
            break;
        else if (array[mid] < target) //��ǥ ���� �߾� ������ ũ�� ���������� �̵�
            left = mid + 1;
        else
            right = mid - 1; //��ǥ ���� �߾� ������ ������ �������� �̵�
    }
    return count;
}

//���� Ž�� ��� �� Ƚ�� ��� �Լ�
double getAverageBinarySearchCompareCount(int* array) {
    double totalCount = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; //�迭���� ������ ���� ��ǥ ������ ����
        totalCount += binarySearch(array, target); //���� Ž�� ���� �� �� Ƚ�� ����
    }
    return totalCount / 100.0;
}

//�迭 ��� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) //ó�� 20�� ���
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) //������ 20�� ���
        printf("%3d ", array[i]);
    printf("\n");
}

int main() {
    srand(time(NULL)); //���� �õ� �ʱ�ȭ
    int array[SIZE];

    generateRandomArray(array); //�迭 ����

    //���� Ž�� ��� �� Ƚ��
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    //�� ���� �� �� Ƚ�� ���
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    //���� Ž�� ��� �� Ƚ��
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    //�迭 ���
    printArray(array);

    return 0;
}

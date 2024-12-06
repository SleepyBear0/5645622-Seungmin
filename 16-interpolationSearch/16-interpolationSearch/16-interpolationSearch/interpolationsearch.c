#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; //0~9999������ ����
    }
}

//��� �Լ�
void printArray(int array[]) {
    printf("Array Sorting Result:\n");
    //�迭 ó�� 20���� ��� ���
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n");
    //�迭 ������ 20�� ��� ���
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n");
}

//������ �Լ�
void QuickSort(int array[], int low, int high) {
    if (low < high) {
        int pivot = array[high]; //�ǹ� ���� �迭�� ������ ������ ����
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (array[j] <= pivot) { //���� ���� �ǹ����� �۰ų� ������
                i++;
                //���� ���� i��° ���� ��ȯ
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;

        //�ǹ� �������� �¿� �����Ͽ� ��������� ���� ����
        QuickSort(array, low, i);
        QuickSort(array, i + 2, high);
    }
}

//����Ž�� �Լ�
int binarySearch(int array[], int target) {
    int low = 0, high = SIZE - 1, compareCount = 0;
    //if���� else if�� �ϳ��� �Բ� ����ϴ� ��� if��, else if�� else�� �ȿ��� compareCountüũ!
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (array[mid] == target) { //Ÿ�� ���� �߰� ���� ������ ����
            compareCount++; //compareCountüũ!
            return compareCount;
        }
        else if (array[mid] < target) { //Ÿ�ٰ��� �� ũ�� ������ Ž��
            compareCount++; //compareCountüũ!
            low = mid + 1;
        }
        else { //Ÿ�ٰ��� �� ������ ���� Ž��
            compareCount++; //compareCountüũ!
            high = mid - 1;
        }
    }
    return compareCount;
}

//����Ž�� �Լ�
int interpolationSearch(int array[], int target) {
    int low = 0, high = SIZE - 1, compareCount = 0;
    while (low <= high && target >= array[low] && target <= array[high]) {
        //while�� �� if�� ���� compareCountüũ
        if (array[high] == array[low]) { //��� ���� ������ ���
            compareCount++; //compareCountüũ!
            if (array[low] == target) { 
                return compareCount;
            }
            break;
        }
        int pos = low + ((target - array[low]) * (high - low)) / (array[high] - array[low]);
        //while�� �ȿ� if���� else if�� �ϳ��� ����ϴ� ���
        if (array[pos] == target) { //Ÿ�� ���� ã���� ����
            compareCount++; //compareCountüũ!
            return compareCount;
        }
        else if (array[pos] < target) { //Ÿ�� ���� �� ũ�� ������ Ž��
            compareCount++; //compareCountüũ!
            low = pos + 1;
        }
        else { //Ÿ�� ���� �� ������ ���� Ž��
            compareCount++; //compareCountüũ!
            high = pos - 1;
        }
    }
    return compareCount;
}

//����Ž�� ��� �� Ƚ���� ����ϴ� �Լ�
double getAverageBinarySearchCompareCount(int array[]) {
    double totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { //1000�� �ݺ�
        int target = array[rand() % SIZE];
        totalCompareCount += binarySearch(array, target); //�� Ƚ�� ����
    }
    return totalCompareCount / 1000.0;
}

//����Ž�� ��� �� Ƚ���� ����ϴ� �Լ�
double getAverageInterpolationSearchComparecount(int array[]) {
    double totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { //1000�� �ݺ�
        int target = array[rand() % SIZE];
        totalCompareCount += interpolationSearch(array, target); //�� Ƚ�� ����
    }
    return totalCompareCount / 1000.0;
}

int main(int argc, char* argv[]) {
    srand(time(NULL)); //���� �õ� �ʱ�ȭ

    int array[SIZE]; //�迭 ����

    generateRandomArray(array); 
    QuickSort(array, 0, SIZE - 1); //������ 

    printArray(array); //���

    //��� �� Ƚ�� ���
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));
    printf("\n"); 
    
    return 0;
}

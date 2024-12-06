#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; //0~9999사이의 난수
    }
}

//출력 함수
void printArray(int array[]) {
    printf("Array Sorting Result:\n");
    //배열 처음 20개의 요소 출력
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n");
    //배열 마지막 20개 요소 출력
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]);
    }
    printf("\n");
}

//퀵정렬 함수
void QuickSort(int array[], int low, int high) {
    if (low < high) {
        int pivot = array[high]; //피벗 값을 배열의 마지막 값으로 설정
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (array[j] <= pivot) { //현재 값이 피벗보다 작거나 같으면
                i++;
                //현재 값과 i번째 값을 교환
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;

        //피벗 기준으로 좌우 분할하여 재귀적으로 정렬 수행
        QuickSort(array, low, i);
        QuickSort(array, i + 2, high);
    }
}

//이진탐색 함수
int binarySearch(int array[], int target) {
    int low = 0, high = SIZE - 1, compareCount = 0;
    //if문을 else if문 하나와 함께 사용하는 경우 if문, else if문 else문 안에서 compareCount체크!
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (array[mid] == target) { //타켓 값이 중간 값과 같으면 종료
            compareCount++; //compareCount체크!
            return compareCount;
        }
        else if (array[mid] < target) { //타겟값이 더 크면 오른쪽 탐색
            compareCount++; //compareCount체크!
            low = mid + 1;
        }
        else { //타겟값이 더 작으면 왼쪽 탐색
            compareCount++; //compareCount체크!
            high = mid - 1;
        }
    }
    return compareCount;
}

//보간탐색 함수
int interpolationSearch(int array[], int target) {
    int low = 0, high = SIZE - 1, compareCount = 0;
    while (low <= high && target >= array[low] && target <= array[high]) {
        //while문 안 if문 에서 compareCount체크
        if (array[high] == array[low]) { //모든 값이 동일한 경우
            compareCount++; //compareCount체크!
            if (array[low] == target) { 
                return compareCount;
            }
            break;
        }
        int pos = low + ((target - array[low]) * (high - low)) / (array[high] - array[low]);
        //while문 안에 if문과 else if문 하나와 사용하는 경우
        if (array[pos] == target) { //타겟 값을 찾으면 종료
            compareCount++; //compareCount체크!
            return compareCount;
        }
        else if (array[pos] < target) { //타겟 값이 더 크면 오른쪽 탐색
            compareCount++; //compareCount체크!
            low = pos + 1;
        }
        else { //타켓 값이 더 작으면 왼쪽 탐색
            compareCount++; //compareCount체크!
            high = pos - 1;
        }
    }
    return compareCount;
}

//이진탐색 평균 비교 횟수를 계산하는 함수
double getAverageBinarySearchCompareCount(int array[]) {
    double totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { //1000번 반복
        int target = array[rand() % SIZE];
        totalCompareCount += binarySearch(array, target); //비교 횟수 누적
    }
    return totalCompareCount / 1000.0;
}

//보간탐색 평균 비교 횟수를 계산하는 함수
double getAverageInterpolationSearchComparecount(int array[]) {
    double totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { //1000번 반복
        int target = array[rand() % SIZE];
        totalCompareCount += interpolationSearch(array, target); //비교 횟수 누적
    }
    return totalCompareCount / 1000.0;
}

int main(int argc, char* argv[]) {
    srand(time(NULL)); //랜덤 시드 초기화

    int array[SIZE]; //배열 선언

    generateRandomArray(array); 
    QuickSort(array, 0, SIZE - 1); //퀵정렬 

    printArray(array); //출력

    //평균 비교 횟수 출력
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));
    printf("\n"); 
    
    return 0;
}

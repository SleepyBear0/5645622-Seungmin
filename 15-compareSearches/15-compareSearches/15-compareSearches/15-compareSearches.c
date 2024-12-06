#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

//비교횟수를 저장하는 변수
int compareCount = 0;

//임의의 배열 생성
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0 ~ 999 사이의 숫자
    }
}

//순차 탐색
int linearSearch(int* array, int target) {
    int count = 0; //비교 횟수
    for (int i = 0; i < SIZE; i++) {
        count++; //비교 횟수 증가
        if (array[i] == target) //현재 요소가 목표값과 같으면 종료
            break;
    }
    return count;
}

//평균 비교 횟수 계산 함수
double getAverageLinearSearchCompareCount(int* array) {
    double totalCount = 0; //총 비교 횟수를 저장하는 변수
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; //배열에서 임의의 값을 타깃으로 설정
        totalCount += linearSearch(array, target); //순차 탐색 수행 및 비교 횟수 누적
    }
    return totalCount / 100.0; //평균 비교 횟수 반환
}

//퀵 정렬함수
void quickSort(int* array, int left, int right) {
    if (left >= right)
        return;
    int pivot = array[left]; //피멋으로 배열의 첫번째 요소 선택
    int i = left + 1;
    int j = right;

    while (i <= j) {
        //왼쪽에서 피벗보다 큰 값을 찾음
        while (i <= right && array[i] <= pivot) {
            i++;
            compareCount++; //비교 횟수 증가
        }
        //오른쪽에서 피벗보다 작은 값을 찾음
        while (j > left && array[j] >= pivot) {
            j--;
            compareCount++; //비교 횟수 증가
        }
        //값 교환
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

//퀵 정렬의 비교 횟수 계산 함수
void getQuickSortCompareCount(int* array) {
    compareCount = 0; //비교 횟수 초기화
    quickSort(array, 0, SIZE - 1);
}

//이진 탐색함수
int binarySearch(int* array, int target) {
    int left = 0, right = SIZE - 1, count = 0;
    while (left <= right) {
        count++; //비교 횟수 증가
        int mid = (left + right) / 2; //중앙 요소의 인덱스 계산
        if (array[mid] == target) //목표 값 찾으면 종료
            break;
        else if (array[mid] < target) //목표 값이 중앙 값보다 크면 오른쪽으로 이동
            left = mid + 1;
        else
            right = mid - 1; //목표 값이 중앙 값보다 작으면 왼쪽으로 이동
    }
    return count;
}

//이진 탐색 평균 비교 횟수 계산 함수
double getAverageBinarySearchCompareCount(int* array) {
    double totalCount = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; //배열에서 임의의 값을 목표 값으로 설정
        totalCount += binarySearch(array, target); //이진 탐색 수행 및 비교 횟수 누적
    }
    return totalCount / 100.0;
}

//배열 출력 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) //처음 20개 출력
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) //마지막 20개 출력
        printf("%3d ", array[i]);
    printf("\n");
}

int main() {
    srand(time(NULL)); //랜덤 시드 초기화
    int array[SIZE];

    generateRandomArray(array); //배열 생성

    //순차 탐색 평균 비교 횟수
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    //퀵 정렬 및 비교 횟수 출력
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    //이진 탐색 평균 비교 횟수
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    //배열 출력
    printArray(array);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

//요소 교환 함수
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//heap 정렬 함수
void resortHeap(int arr[], int n, int i) {
	int largest = i; //현재 노드가 가장 큰 값
	int left = 2 * i + 1; //왼쪽 자식 (0)
	int right = 2 * i; //오른쪽 자식 (1)

	//왼쪽 자식이 존재하면서 왼쪽 자식이 더 크면 왼쪽 자식이 가장 큰 값 
	if (left < n && arr[left]>arr[largest])
		largest = left;

	//오른쪽 자식이 존재하면서 오른쪽 자식이 더 크면 오른쪽 자식이 가장 큰 값 
	if (right <n && arr[right]>arr[largest])
		largest = right;
	
	//가장 큰 값이 현재 노드가 아니라면 교환, resortHeap 재호출
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		resortHeap(arr, n, largest);
	}
}

//max heap 삽입함수
void insertHeap(int arr[], int n) {
	int i = n;
	//부모 노드가 현재 노드보다 작으면 부모와 교환, 힙 거슬러 올라가기
	while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
		swap(&arr[i], &arr[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	//힙 출력
	for (int j = 0; j <= n; j++) {
		printf("%d ", arr[j]);
	}
	printf("\n");
}

//max heap 생성하는 함수
void BuildMaxHeap(int arr[], int n) {
	//첫 번째 요소 출력
	printf("%d\n", arr[0]);
	//두 번째 요소부터 힙에 삽입
	for (int i = 1; i < n; i++) {
		insertHeap(arr, i);
	}
}

//max heap을 사용해서 정렬하기 위한 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
	// max heap 생성하는 함수
	BuildMaxHeap(inputData, n);
	// 하나씩 힙에서 루트(최대값)를 제거하고 정렬
	for (int i = n - 1; i > 0; i--) {
		//최대값과 마지막 요소의 교환
		swap(&inputData[0],&inputData[i]);
		resortHeap(inputData, i, 0);
		// 힙 재정렬 후 상태 출력
		for (int j = 0; j < i; j++) {
			printf("%d ", inputData[j]);
		}
		printf("\n");
	}
}

int main() {
	int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
	int size = sizeof(inputData) / sizeof(inputData[0]);
	// 힙 정렬 실행
	printf("<Sort>\n");
	BuildMaxHeapAndSort(inputData, size);
	// 정렬된 결과 출력
	printf("\nSorted Array:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", inputData[i]);
	}
	printf("\n");
	return 0;
}

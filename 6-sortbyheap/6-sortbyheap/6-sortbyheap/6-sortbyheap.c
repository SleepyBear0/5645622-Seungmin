#include <stdio.h>
#include <stdlib.h>

//��� ��ȯ �Լ�
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//heap ���� �Լ�
void resortHeap(int arr[], int n, int i) {
	int largest = i; //���� ��尡 ���� ū ��
	int left = 2 * i + 1; //���� �ڽ� (0)
	int right = 2 * i; //������ �ڽ� (1)

	//���� �ڽ��� �����ϸ鼭 ���� �ڽ��� �� ũ�� ���� �ڽ��� ���� ū �� 
	if (left < n && arr[left]>arr[largest])
		largest = left;

	//������ �ڽ��� �����ϸ鼭 ������ �ڽ��� �� ũ�� ������ �ڽ��� ���� ū �� 
	if (right <n && arr[right]>arr[largest])
		largest = right;
	
	//���� ū ���� ���� ��尡 �ƴ϶�� ��ȯ, resortHeap ��ȣ��
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		resortHeap(arr, n, largest);
	}
}

//max heap �����Լ�
void insertHeap(int arr[], int n) {
	int i = n;
	//�θ� ��尡 ���� ��庸�� ������ �θ�� ��ȯ, �� �Ž��� �ö󰡱�
	while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
		swap(&arr[i], &arr[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
	//�� ���
	for (int j = 0; j <= n; j++) {
		printf("%d ", arr[j]);
	}
	printf("\n");
}

//max heap �����ϴ� �Լ�
void BuildMaxHeap(int arr[], int n) {
	//ù ��° ��� ���
	printf("%d\n", arr[0]);
	//�� ��° ��Һ��� ���� ����
	for (int i = 1; i < n; i++) {
		insertHeap(arr, i);
	}
}

//max heap�� ����ؼ� �����ϱ� ���� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
	// max heap �����ϴ� �Լ�
	BuildMaxHeap(inputData, n);
	// �ϳ��� ������ ��Ʈ(�ִ밪)�� �����ϰ� ����
	for (int i = n - 1; i > 0; i--) {
		//�ִ밪�� ������ ����� ��ȯ
		swap(&inputData[0],&inputData[i]);
		resortHeap(inputData, i, 0);
		// �� ������ �� ���� ���
		for (int j = 0; j < i; j++) {
			printf("%d ", inputData[j]);
		}
		printf("\n");
	}
}

int main() {
	int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
	int size = sizeof(inputData) / sizeof(inputData[0]);
	// �� ���� ����
	printf("<Sort>\n");
	BuildMaxHeapAndSort(inputData, size);
	// ���ĵ� ��� ���
	printf("\nSorted Array:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", inputData[i]);
	}
	printf("\n");
	return 0;
}

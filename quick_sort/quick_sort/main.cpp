#include <stdio.h>
#define N_MAX 1000

int arr1[10] = { 1, 50, 34, 22, 22, 11, 33, 1, 2, 1 };
int arr2[10] = { 1, 50, 34, 22, 22, 11, 33, 1, 2, 1 };


void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}



// recursive
void quick_sort(int arr[], int first, int last) {
	int pivot = first;
	int i, j;

	if (first < last) {
		
		i = first;
		j = last;

		while (i < j) {
			while (arr[i] <= arr[pivot] && i < last)
				i++;
			while (arr[j] > arr[pivot])
				j--;

			if (i < j)
				swap(arr, i, j);
		}
		swap(arr, j, pivot);

		quick_sort(arr, first, j - 1);
		quick_sort(arr, j + 1, last);
	}
}

// stack
void quick_sort2(int arr[], int first, int last) {
	int pivot, i, j;
	int stack[N_MAX];
	int idx_stack = 0;

	stack[idx_stack++] = last;
	stack[idx_stack++] = first;

	while (idx_stack > 0) {
		first = stack[--idx_stack];
		last = stack[--idx_stack];
		pivot = first;
		i = first;
		j = last;
		
		if (i < j) {
			while (i < j) {
				while (arr[i] <= arr[pivot] && i < last)
					i++;
				while (arr[j] > arr[pivot])
					j--;

				if (i < j)
					swap(arr, i, j);
			}
			swap(arr, j, pivot);

			stack[idx_stack++] = j - 1;
			stack[idx_stack++] = first;
			stack[idx_stack++] = last;
			stack[idx_stack++] = j + 1;
		}
	}
}


int main() {

	quick_sort(arr1, 0, 9);
	for (register int i = 0; i < 10; ++i) {
		printf("%d ", arr1[i]);
	}
	printf("\n\n");

	quick_sort2(arr2, 0, 9);
	for (register int i = 0; i < 10; ++i) {
		printf("%d ", arr2[i]);
	}


	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE 20

int* createArray(int size){
	int *tmpArray = (int *)malloc(sizeof(int) * size);
	for (int i = 1; i <= size; i++){
		*(tmpArray + i -1) = rand()%10;
	}
	return tmpArray;
}

int* duplicateArray(int *p, int size){
	int *tmpArray = (int *)malloc(sizeof(int) * size);
	for (int i = 1; i <= size; i++){
		*(tmpArray + i -1) = *(p + i -1);
	}
	return tmpArray;
}	//can use memcpy(void *dest, void* src, size_t size);
void printArray(int *array, int size){
	for (int i = 1; i <= size; i++){
		printf("%5d", *(array + i -1));
	}
}

void exch(int *array, int first, int second){
	int tmp = *(array + first);
	*(array + first) = *(array + second);
	*(array + second) = tmp;
}

void sortThreeWayPartition(int array[], int left, int right)
{
	if (right <= left) return;
	int i = left - 1, j = right;
	int p = left - 1, q = right;
	while (1){
		while ( array[++i] < array[right]);
		while (array[right] < array[--j]){
			if (j==1) break;
		}
		if (i > j) break;
		exch(array, i ,j);		//write this func
		if (array[i] == array[right])
			exch(array, ++p, i);
		if (array[j] == array[right])	
			exch(array, --q, j);
	}
	exch(array, i ,right);
	j = i - 1;
	i = i +1;
	for (int k = 1; k <= p; k++)
		exch(array, k, j--);
	for (int k = right - 1; k >= q; k--)
		exch(array, k, i++);
	sortThreeWayPartition(array, left, j);
	sortThreeWayPartition(array, i, right);
}

int main()
{
	int *array1;
	int *array2;
	array1 = createArray(ARRAY_SIZE);
	array2 = duplicateArray(array1, ARRAY_SIZE);
	printf("\nArray 1: ");
	printArray(array1, ARRAY_SIZE);
	sortThreeWayPartition(array1,0,ARRAY_SIZE -1);
	printf("\nResult: ");
	printArray(array1, ARRAY_SIZE);
}
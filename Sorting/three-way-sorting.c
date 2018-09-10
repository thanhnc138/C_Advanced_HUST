#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 20

//initialize data
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

//sorting
void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int arr[],int low, int high)
{
    // pivot (Element to be placed at right position)
    int pivot = arr[high];  
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++){
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot){
            i++;    // increment index of smaller element
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i + 1],&arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high){
        /* pi is partitioning index, arr[pi] is now
           at right place */
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);  // Before pivot
        quickSort(arr, pivot + 1, high); // After pivot
    }
}

void exchange1(int array[], int i, int j){
	int tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}
void exchange(int *array, int i, int j){
	int tmp = *(array+i);
	*(array+i) = *(array+j);
	*(array+j) = tmp;
}
void sortTwoWayPartition(int array[], int left, int right)
{
	if (right <= left) return;
	int i = left - 1, j = right;
	while (1){
		while ( array[++i] < array[right]);
		while (array[right] < array[--j]){
			if (j==1) break;
		}
		if (i > j) break;
		exchange(array, i ,j);		//write this func
	}
	exchange(array, i ,right);
	j = j - 1;
	i = i + 1;
	sortTwoWayPartition(array, left, j);
	sortTwoWayPartition(array, i, right);
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
		exchange(array, i ,j);		//write this func
		if (array[i] == array[right])
			exchange(array, ++p, i);
		if (array[j] == array[right])	
			exchange(array, --q, j);
	}
	exchange(array, i ,right);
	j = j - 1;
	i = i +1;
	for (int k = 1; k <= p; k++)
		exchange(array, k, j--);
	for (int k = right - 1; k >= q; k--)
		exchange(array, k, i++);
	sortThreeWayPartition(array, left, j);
	sortThreeWayPartition(array, i, right);
}
int main()
{
	int *array1;
	int *array2;
	srand(time(0));		//refresh the random number
	array1 = createArray(ARRAY_SIZE);
	array2 = duplicateArray(array1, ARRAY_SIZE);
	printf("\nArray 1: ");
	printArray(array1, ARRAY_SIZE);

	//check the performance
	time_t start, end;
	volatile long unsigned t;

	//2 way paritition
	start = time(NULL);
	sortTwoWayPartition(array1,0,ARRAY_SIZE -1);
	printf("\nResult: ");
	printArray(array1, ARRAY_SIZE);
	end = time(NULL);
	printf("\nRunning time for 2 way partition: %f secs. ", difftime(end,start));

	//3 way paritition
	start = time(NULL);
	sortThreeWayPartition(array2,0,ARRAY_SIZE -1);
	printf("\nResult: ");
	printArray(array2, ARRAY_SIZE);
	end = time(NULL);
	printf("\nRunning time for 3 way partition: %f secs. ", difftime(end,start));
}
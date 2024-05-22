#include <stdio.h> 
#include <stdlib.h> 

void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; //mid-left-1 ie left side array length
	int n2 = r - m; //right side array length

	int L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1 + j]; 

	i = 0; j=0; 
	k = l; 
	while (i < n1 && j < n2) {   //loop runs through both new arrays simultaneously
		if (L[i] <= R[j]) {    // compares all the elements of l with R[j]
			arr[k] = L[i];        //l smaller placed in main old array, the same array is over written (reduce space complexity)
			i++; 
		} 
		else { 
			arr[k] = R[j];  // else r's elements are smaller so they are placed in old array 
			j++; 
		} 
		k++; 
	} 

	while (i < n1) {  //if the left array has more elemnts then right array this will place the elements
		arr[k] = L[i]; //the right has been checked and exhausted hence only the elements that are in left are greater so are placed directly
		i++; 
		k++; 
	} 
 
	while (j < n2) { //similsr case when right elements remain
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

void mergeSort(int arr[], int l, int r) 
{ 
	if (l < r) { 
		 
		int m = l + (r - l) / 2; 
 
		mergeSort(arr, l, m); 
		mergeSort(arr, m + 1, r); 

		merge(arr, l, m, r); 
	} 
} 

void printArray(int A[], int size) 
{ 
	int i; 
	for (i = 0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
} 


int main() 

{   int n;
	printf("Enter the number of elements that you want to sort: ");
    scanf("%d", &n);
	int arr[n];
	printf("\nEnter the elements that you want to sort: ");
	for(int i=0;i<n;i++)
	{
       scanf("%d", &arr[i]);
	}
	printf("Given array is: \n"); 
	printArray(arr,n); 

	mergeSort(arr, 0, n - 1); 

	printf("\nSorted array is: \n"); 
	printArray(arr, n); 
	return 0; 
}
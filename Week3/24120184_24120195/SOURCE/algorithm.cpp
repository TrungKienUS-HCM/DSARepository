#include <iostream>
#include <climits>
#include "header.h"

using namespace std;

// BUBBLE SORT
void bubbleSort(int* arr, int n) {
	for (int i = 0; i < n; ++i) {
		bool swapped = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

// SELECTION SORT
void selectionSort(int* arr, int n) {
	for (int i = 0; i < n - 1; ++i) {
		int min = i;
		for (int j = i + 1; j < n; ++j) {
			if (arr[j] < arr[min]) min = j;
		}
		swap(arr[min], arr[i]);
	}
}

// INSERTION SORT
void insertionSort(int* arr, int n) {
	for (int i = 1; i < n; ++i) {
		int x = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > x) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = x;
	}
}

// MERGE SORT
void merge(int* arr, int left, int mid, int right) {
	int* half1 = new int[mid - left + 1];
	copy(arr + left, arr + mid + 1, half1);
	int* half2 = new int[right - mid];
	copy(arr + mid + 1, arr + right + 1, half2);

	int i = 0, j = 0, mark = left;
	while (i < mid - left + 1 && j < right - mid) {
		if (half1[i] < half2[j]) arr[mark++] = half1[i++];
		else arr[mark++] = half2[j++];
	}

	while (i < mid - left + 1) arr[mark++] = half1[i++];
	while (j < right - mid) arr[mark++] = half2[j++];

	delete[] half1;
	delete[] half2;
}

void mergeSort(int* arr, int left, int right) {
	if (left >= right) return;
	int mid = (left + right) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

// HEAP SORT
void heapify(int* arr, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;
	if (right < n && arr[right] > arr[largest])
		largest = right;

	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heapSort(int* arr, int n) {
	for (int i = n / 2 - 1; i >= 0; --i)
		heapify(arr, n, i);

	for (int i = n - 1; i >= 0; --i) {
		swap(arr[i], arr[0]);
		heapify(arr, i, 0);
	}
}

// QUICK SORT
int partition(int* arr, int left, int right) {
    int iPivot = left + rand() % (right - left);
    swap(arr[iPivot], arr[right]);
    int pivot = arr[right];
    int i = left - 1;
    int j = left;
    for (; j < right; ++j) {
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[++i], arr[right]);
    return i;
}

void quickSort(int* arr, int left, int right) {
    if (left >= right) return;
    int p = partition(arr, left, right);
    quickSort(arr, left, p - 1);
    quickSort(arr, p + 1, right);
}

// RADIX SORT
void countingSort(int* arr, int n, int exp) {
	int* output = new int[n];
	int count[10] = { 0 };

	for (int i = 0; i < n; ++i)
		count[(arr[i] / exp) % 10]++;

	for (int i = 1; i < 10; ++i)
		count[i] += count[i - 1];

	for (int i = n - 1; i >= 0; --i) {
		int digit = (arr[i] / exp) % 10;
		output[count[digit] - 1] = arr[i];
		count[digit]--;
	}

	copy(output, output + n, arr);
	delete[] output;
}

int findMax(int* arr, int n) {
	int max = arr[0];
	for (int i = 1; i < n; ++i){
		if (arr[i] > max) max = arr[i];
	}
	return max;
}

void radixSort(int* arr, int n) {
	int maxNum = findMax(arr, n);
	for (int exp = 1; maxNum / exp > 0; exp *= 10)
		countingSort(arr, n, exp);
}

//Shaker Sort
void shakerSort(int *arr, int n)
{
	int left = 0;
	int right = n - 1;
	int k = 0;
	while (left < right)
	{
		for (int i = left; i < right; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				k = i;
			}
		}
		right = k;
		for (int i = right; i > left; i--)
		{
			if (arr[i] < arr[i - 1])
			{
				swap(arr[i], arr[i - 1]);
				k = i;
			}
		}
		left = k;
	}
}

//SHELL SORT
void shellSort(int *arr,int n)
{
	int h = 1;
	while (h < n / 3)
	{
		h = h * 3 + 1;
	}
	while (h > 0)
	{	
		for (int i = h; i < n ;i++)
		{
			int temp = arr[i];
			int j = i;
			while (j >= h && arr[j - h] > temp)
			{
				arr[j] = arr[j - h];
				j = j - h;
			}
			arr[j] = temp;
		}
		h = (h - 1) / 3;
	}
}

//COUNTING SORT
void countingSort(int *arr,int n)
{	
	int max =INT_MIN;
	for (int t = 0; t < n ;t++)
	{
		if (max < arr[t])
		{
			max = arr[t];
		}
	}
	int *cnt = new int[max + 1]();
	for (int i = 0; i < n ;i++)
	{
		cnt[arr[i]]++;
	}

	int i = 0;
	for (int j = 0;j <= max ;j++)
	{
		while (cnt[j] > 0)
		{
			cnt[j]--;
			arr[i] = j;
			i++;
		}
	}

	delete[] cnt;
}

void flashSort(int *arr, int n) {
    if (n <= 1) return;
        int m = n * 0.43;
    if (m <= 2) m = 2;

    int *bucket = new int[m]();

    int Max = arr[0], Min = arr[0];
    for (int i = 1; i < n; ++i) {
        if (Max < arr[i]) Max = arr[i];
        if (Min > arr[i]) Min = arr[i];
    }
    if (Max == Min)
    {
        delete[] bucket;
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        int k = 1ll * (m - 1) * (arr[i] - Min) / (Max - Min);
        ++bucket[k];
    }

    for (int i = 1; i < m; ++i)
        bucket[i] += bucket[i - 1];

    int count = 0;
    int i = 0;
    while (count < n) {
        int k = 1ll * (m - 1) * (arr[i] - Min) / (Max - Min);
        while (i >= bucket[k]) {
            ++i;
            k = 1ll * (m - 1) * (arr[i] - Min) / (Max - Min);
        }        
        int z = arr[i];
        while (i != bucket[k]) {
            k = 1ll * (m - 1) * (z - Min) / (Max - Min);
            int y = arr[bucket[k] - 1];
            arr[--bucket[k]] = z;
            z = y;
            ++count;
        }
    }   
    
    insertionSort(arr,n);
    
    delete[] bucket;
}
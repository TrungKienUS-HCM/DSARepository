#ifndef header
#define header

#include <iostream>
#include <climits>

using namespace std;

// BUBBLE SORT
void bubbleSort(int* arr, int n);

// SELECTION SORT
void selectionSort(int* arr, int n);

// INSERTION SORT
void insertionSort(int* arr, int n);

// MERGE SORT
void merge(int* arr, int left, int mid, int right);

void mergeSort(int* arr, int left, int right);

// HEAP SORT
void heapify(int* arr, int n, int i);

void heapSort(int* arr, int n);

// QUICK SORT
int partition(int* arr, int left, int right);

void quickSort(int* arr, int left, int right);

// RADIX SORT
void countingSort(int* arr, int n, int exp);

int findMax(int* arr, int n);

void radixSort(int* arr, int n);

//SHAKER SORT
void shakerSort(int *arr,int n);

//SHELL SORT
void shellSort(int *arr,int n);

//COUNTING SORT
void countingSort(int *arr,int n);

//FLASH SORT
void flashSort(int *arr,int n);

#endif
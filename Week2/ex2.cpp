#include <iostream>
using namespace std;

int linearSearchSetinel(int* arr, int n, int K) {
	// Put the key element at the end of the array
	// We check if the last element is the element we need to find
	if (arr[n - 1] == K) return n - 1;
	// Store the last element and replace it with the key element
	int last = arr[n - 1];
	arr[n - 1] = K;

	// Iterate through the array to find the key element
	int i = 0;
	while (arr[i] != K) ++i;

	// Restore the last element
	arr[n - 1] = last;
	// If the element found is not the element that we put at the end of the array, it's the element we need to find
	if (i < n - 1) return i;
	// Otherwise, it's just the setinel
	else return -1;
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	int K;
	cin >> K;
	cout << linearSearchSetinel(arr, n, K);
	delete[] arr;
}
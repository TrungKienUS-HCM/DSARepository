#include <iostream>
using namespace std;

bool isSorted(int arr[], int n) {
	// The base case: an array with just 1 or 0 elements is always sorted
	if (n <= 1) return true;
	// Checking if the last 2 elements are in order
	if (arr[n - 2] > arr[n - 1]) return false;
	// Recursively check the top (n - 1) elements of the array
	return isSorted(arr, n - 1);
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> arr[i];
	if (isSorted(arr, n))
		cout << "The array is sorted." << endl;
	else cout << "The array is NOT sorted. " << endl;
	delete[] arr;
}
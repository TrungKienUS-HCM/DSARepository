#include <iostream>
#include <algorithm>
using namespace std;

// Define a function to display the triplet of indices properly
void printTriplet(int* arr, int i, int j, int k) {
	cout << "[" << arr[i] << ", " << arr[j] << ", " << arr[k] << "] " << endl;
}

void findSum0Triplets(int* arr, int n) {
	// We have to sort the whole array in ascending order
	// In order to preserve the initial array, we use another back-up one
	int* backUp = new int[n];
	copy(arr, arr + n, backUp);
	// Sort the array to make the searching process easier
	sort(arr, arr + n);
	// We perform a nested for loop to take 2 elements for the sum
	for (int i = 0; i < n; ++i) {
		// To avoid processing duplicate triplets, we skip duplicate values of ith number in the array
		if (i > 0 and arr[i] == arr[i - 1]) continue;
		for (int j = i + 1; j < n; ++j) {
			// We use binary search to search for the third number that makes the sum 0
			// Since all of the elements before index i have already been processed, the j index has to be greater than i
			int left = j + 1, right = n - 1;
			int sum = arr[i] + arr[j];
			while (left <= right) {
				int mid = (left + right) / 2;
				// If there's a number whose sum with arr[i] and arr[j] equals 0, we display that triplet, terminate the while-loop
				// and search for another triplet
				if (sum + arr[mid] == 0) {
					printTriplet(arr, i, j, mid);
					break;
				}
				// Otherwise, we narrow the search range
				else if (sum + arr[mid] < 0)
					left = mid + 1;
				else right = mid - 1;
			}
		}
	}
	// Restore the initial array and delete the back-up one
	copy(backUp, backUp + n, arr);
	delete[] backUp;
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	findSum0Triplets(arr, n);
	delete[] arr;
}
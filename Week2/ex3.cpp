#include <iostream>
using namespace std;

// Using binary search to find the minimum element of a sorted and rotated array
int findRotatedMin(int* arr, int n) {
	int left = 0, right = n - 1;
	while (left < right) {
		int mid = (left + right) / 2;
		// Since the array is rotated after it's sorted in an ascending order, the array after being 
		// rotated will be divided into 2 parts. We must determine which part is the mid element in.
		// If it's in the rotated part, we narrow the search range to the right.
		// Since the minimum element must be in the original part of the array that has been pushed to the right due to the rotation.
		if (arr[mid] > arr[right]) left = mid + 1;
		else right = mid;
	}
	return arr[left];
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	cout << findRotatedMin(arr, n);
	delete[] arr;
}
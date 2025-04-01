#include <iostream>
using namespace std;

// Check if there's any subarray in the array whose the summary of all elements equal or greater than the target
bool CheckSubArrayTotal(int* arr, int n, int length, int target) {
	// We create a prefix sum array of the array to check the summary of any subarray of length length
	int* prefix = new int[n + 1];
	prefix[0] = 0;
	for (int i = 1; i <= n; ++i) prefix[i] = arr[i - 1] + prefix[i - 1];
	// Iterate through the prefix sum array to find any subarray whose summary can satisfy the condition
	int i = length + 1;
	for (; i <= n; ++i) {
		// If there's a subarray like that, we get out of the loop
		if (prefix[i] - prefix[i - length] >= target) break;
	}
	delete[] prefix;
	// if i has not gone beyond the array, it means that there's a subarray in the array can satisfy the condition
	if (i <= n) return true;
	return false;
}

int FindMinimalLength(int* arr, int n, int target) {
	int min = 1;
	int max = n;
	while (min < max) {
		// we find an average number of elements in a subarray
		int average = (min + max) / 2;
		// Then we check if there's any subarray whose that average number of elements can satisfy the condition
		// We narrow the search range to the left to check for some smaller numbers of average elements
		if (CheckSubArrayTotal(arr, n, average, target)) max = average;
		// Otherwise, we narrow the range to the right to check for some bigger numbers
		else min = average + 1;
	}
	// Return the minimum length
	return min;
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	int target;
	cin >> target;
	cout << FindMinimalLength(arr, n, target) << endl;
	delete[] arr;
}
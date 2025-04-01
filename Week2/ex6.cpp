#include <iostream>
using namespace std;

bool CheckTargetSum(int* arr, int n, int target) {
	// We perform a for loop to take an element as the first operand of the sum
	for (int i = 0; i < n and arr[i] <= target / 2; ++i) {
		// Then we use binary search to find another number in the array that, when added to the number from the for loop, equals the target
		int left = i + 1;
		int right = n - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			// If the sum equals the target, we return true immediately
			if (arr[mid] + arr[i] == target) return true;
			// Otherwise, we narrow the search range
			else if (arr[mid] + arr[i] > target) right = mid - 1;
			else left = mid + 1;
		}
	}
	// After searching the whole array and there's no pair is found that sums to the target, we return false
	return false;
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	int target;
	cin >> target;
	if (CheckTargetSum(arr, n, target)) cout << "YES" << endl;
	else cout << "NO" << endl;
	delete[] arr;
}

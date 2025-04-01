#include <iostream>
using namespace std;

int linearSearch(int* arr, int n, int K) {
	// iterate through the whole array, check every element to find the key
	for (int i = 0; i < n; ++i) {
		if (arr[i] == K)
			// if the key is found, return its index and terminate the function
			return i;
	}
	// if the key element isn't found in the array, return -1
	return -1;
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) cin >> arr[i];
	int K;
	cin >> K;
	cout << linearSearch(arr, n, K);
	delete[] arr;
}
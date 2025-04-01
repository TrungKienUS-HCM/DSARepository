#include <iostream>
#include <algorithm>
using namespace std;

// Check if the ship is able to convey the packages with limit wLimit in days days.
bool AbleToConvey(int* arr, int n, int days, int wLimit) {
	// the initial value of dayConvey is not 0 because we can't count the last day in the function.
	int dayConvey = 1;
	int weightInDay = 0;
	for (int i = 0; i < n; ++i) {
		if (weightInDay + arr[i] > wLimit) {
			weightInDay = 0;
			++dayConvey;
		}
		weightInDay += arr[i];
	}
	// If the ship can convey all of the packages with the limit of wLimit less than days days.
	return dayConvey <= days;
}

// Get sum of all packages' weight
int sumWeights(int* arr, int n) {
	if (n <= 0) return arr[0];
	return arr[n] + sumWeights(arr, n - 1);
}

// Get the max weight of the packages
int maxWeights(int* arr, int n, int max = 0) {
	if (n < 0) return max;
	if (arr[n] > max) max = arr[n];
	return maxWeights(arr, n - 1, max);
}

int weightCapacity(int* arr, int n, int day) {
	// Assume that the minimum capacity of the ship is the weight of the heaviest packages
	// The maximum could be the sum of all packages' weight
	int minWeight = maxWeights(arr, n - 1);
	int maxWeight = sumWeights(arr, n - 1);
	cout << minWeight << ' ' << maxWeight << endl;

	while (minWeight < maxWeight) {
		int mid = (minWeight + maxWeight) / 2;
		// If mid is the limit capacity of the ship and it's still able to convey all of those within the number of days given, 
		// we cut down on the limit by narrowing the search range to the left of the array.
		// It's because the limit is still high for the ship to convey.
		if (AbleToConvey(arr, n, day, mid)) maxWeight = mid;
		// Otherwise, the limit is too small for conveying within day days.
		else minWeight = mid + 1;
	}

	// Return the minimum capacity.
	return minWeight;
}

int main() {
	int n;
	cin >> n;
	int* weights = new int[n];
	for (int i = 0; i < n; ++i) cin >> weights[i];
	int day;
	cin >> day;
	cout << weightCapacity(weights, n, day);
}
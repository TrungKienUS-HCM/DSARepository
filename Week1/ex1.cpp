#include <iostream>
using namespace std;


int fibonacci(int n) {
	// The base case: fibonacci(0) and fibonacci(1) both equal to 1
	if (n <= 1) return n;
	// Recursive call to the previous 2 numbers in the Fibonacci sequence
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cout << fibonacci(i) << ' ';
}
#include <iostream>
using namespace std;

int factorial(int n) {
	// The base case
	if (n <= 2) return n;
	// The recursive call: Factorial of a number n = n * factorial (n - 1), means that n! = n * (n - 1)!
	return n * factorial(n - 1);
}

int main() {
	int n;
	cin >> n;
	cout << factorial(n);
}
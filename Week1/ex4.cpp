#include <iostream>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
	// When there's just 1 disk left, we can move it easily from the starting rod to the destination rod
	if (n == 1) {
		cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl;
		return;
	}
	// Firstly, move n - 1 disks on the top of the stack from the starting rod to the auxiliary rod
	// On the purpose of leaving the only largest disk on the stack
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
	// Moving that largest disk to the destination rod
	cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
	// Moving the n - 1 disks on the auxiliary rod to the destination rod
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
	// finish moving n disks
}

int main() {
	int n;
	cin >> n;
	towerOfHanoi(n, 'A', 'C', 'B');
}
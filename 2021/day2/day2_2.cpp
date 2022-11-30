#include <bits/stdc++.h>
using namespace std;

int main () {
	int x = 0, z = 0, aim = 0;
	string move;
	int amount;
	while (cin >> move && cin >> amount) {
		switch(move[0]) {
		case 'f':
			x += amount;
			z += aim * amount;
			break;
		case 'd':
			aim += amount;
			break;
		case 'u':
			aim -= amount;
			break;
		default:
			cout << "You shouldn't be here. Go away!" << endl;
			exit(-1);
		}
	}
	cout << (x * z) << endl;
	return 0;
}
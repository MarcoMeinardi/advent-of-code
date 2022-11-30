#include <bits/stdc++.h>
using namespace std;

int main () {
	int p[2] = {2, 7};
	int s[2] = {0, 0};
	int d = 1;
	uint8_t turn = 1;

	p[0]--, p[1]--;

	while(s[turn] < 1000) {
		turn ^= 1;
		p[turn] = (p[turn] + d * 3 + 3) % 10;
		s[turn] += p[turn] + 1;
		d += 3;
	}

	cout << (min(s[0], s[1]) * (d - 1)) << endl;
	return 0;
}
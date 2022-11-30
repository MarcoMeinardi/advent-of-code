#include <bits/stdc++.h>
using namespace std;

int main () {
	long fish[9] = {};
	long cycled;
	int n;

	while (scanf("%d%*c", &n) == 1) {
		fish[n]++;
	}

	for (int i = 0; i < 256; i++) {
		cycled = fish[0];
		for(int j = 0; j < 8; j++) {
			fish[j] = fish[j + 1];
		}
		fish[8] = cycled;
		fish[6] += cycled;
	}

	cout << (long)accumulate(fish, fish + 9, 0L) << endl;
	return 0;
}
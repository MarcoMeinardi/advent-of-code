#include <bits/stdc++.h>
using namespace std;

int main () {
	bool mat[101][101][101] = {};
	char oo[4];
	int x1, x2, y1, y2, z1, z2;
	int tot = 0;

	while(scanf("%s x=%d..%d,y=%d..%d,z=%d..%d", oo, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
		for (int x = max(-50, x1) + 50; x <= min(50, x2) + 50; x++) {
			for (int y = max(-50, y1) + 50; y <= min(50, y2) + 50; y++) {
				for (int z = max(-50, z1) + 50; z <= min(50, z2) + 50; z++) {
					mat[x][y][z] = oo[1] == 'n';
				}
			}
		}
	}

	for (int x = 0; x < 101; x++) {
		for (int y = 0; y < 101; y++) {
			for (int z = 0; z < 101; z++) {
				tot += mat[x][y][z];
			}
		}
	}
	cout << tot << endl;
	return 0;
}
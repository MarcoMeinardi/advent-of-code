#include <bits/stdc++.h>
using namespace std;

bool grid[100][100][100];

const int dx[6] = {1, 0, 0, -1, 0, 0}, dy[6] = {0, 1, 0, 0, -1, 0}, dz[6] = {0, 0, 1, 0, 0, -1};

int main () {
	int x, y, z;
	while (scanf("%d,%d,%d", &x, &y, &z) == 3) {
		grid[x][y][z] = true;
	}

	int tot = 0;
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			for (int z = 0; z < 100; z++) {
				if (!grid[x][y][z]) continue;
				for (int i = 0; i < 6; i++) {
					int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
					if (nx < 0 || ny < 0 || nz < 0 || nx >= 100 || ny >= 100 || nz >= 100 || !grid[nx][ny][nz]) {
						tot++;
					}
				}
			}
		}
	}

	cout << tot << endl;
}

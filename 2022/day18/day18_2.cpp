#include <bits/stdc++.h>
using namespace std;

bool grid[102][102][102];
bool vis[102][102][102];

const int dx[6] = {1, 0, 0, -1, 0, 0}, dy[6] = {0, 1, 0, 0, -1, 0}, dz[6] = {0, 0, 1, 0, 0, -1};

int dfs(int x, int y, int z) {
	if (vis[x][y][z]) return 0;
	vis[x][y][z] = true;

	int tot = 0;
	for (int i = 0; i < 6; i++) {
		int nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
		if (nx < 0 || ny < 0 || nz < 0 || nx >= 102 || ny >= 102 || nz >= 102 || vis[nx][ny][nz]) continue;
		if (grid[nx][ny][nz]) {
			tot += 1;
		} else {
			tot += dfs(nx, ny, nz);
		}
	}

	return tot;
}


int main () {
	int x, y, z;
	while (scanf("%d,%d,%d", &x, &y, &z) == 3) {
		grid[x + 1][y + 1][z + 1] = true;
	}

	cout << dfs(0, 0, 0) << endl;
}

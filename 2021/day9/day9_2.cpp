#include <bits/stdc++.h>
using namespace std;

const int dy[4] = {0, 1, 0, -1};
const int dx[4] = {1, 0, -1, 0};


bool is_low (uint8_t (*grid)[100], int y, int x, int h, int w) {
	int ny, nx;
	for (int i = 0; i < 4; i++) {
		ny = y + dy[i], nx = x + dx[i];
		if (ny >= 0 && ny < h && nx >= 0 && nx < w && grid[y][x] >= grid[ny][nx]) {
			return false;
		}
	}
	return true;
}

int expand (uint8_t (*grid)[100], bool (*vis)[100], int y, int x, int h, int w) {
	if (vis[y][x] || grid[y][x] == 9) {
		return 0;
	}
	int tot = 1;
	int ny, nx;
	vis[y][x] = true;

	for (int i = 0; i < 4; i++) {
		ny = y + dy[i], nx = x + dx[i];
		if (ny >= 0 && ny < h && nx >= 0 && nx < w && grid[ny][nx] >= grid[y][x]) {
			tot += expand(grid, vis, ny, nx, h, w);
		}
	}
	return tot;
}

int main () {
	uint8_t grid[100][100];
	bool vis[100][100] = {};
	int h, w;
	char foo;

	int size;
	int m1 = 0, m2 = 0, m3 = 0;

	for (h = 0; ; h++) {
		for (int j = 0;  ; j++) {
			if (scanf("%c", &foo) != 1) goto end_read;
			if (foo == '\n') {
				w = j;
				break;
			}

			grid[h][j] = foo - '0';
		}
	}
	end_read:

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (!vis[y][x] && is_low(grid, y, x, h, w)) {
				size = expand(grid, vis, y, x, h, w);
				if (size > m1) {
					m3 = m2, m2 = m1, m1 = size;
				} else if (size > m2) {
					m3 = m2, m2 = size;
				} else if (size > m3) {
					m3 = size;
				}
			}
		}
	}

	cout << (m1 * m2 * m3) << endl;

	return 0;
}
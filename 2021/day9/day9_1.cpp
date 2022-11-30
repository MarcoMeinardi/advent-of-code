#include <bits/stdc++.h>
using namespace std;

const int dy[4] = {0, 1, 0, -1};
const int dx[4] = {1, 0, -1, 0};

int main () {
	uint8_t grid[100][100];
	int h, w;
	char foo;
	int ny, nx;
	bool ok;

	int res = 0;

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
			ok = true;
			for(int i = 0; i < 4; i++) {
				ny = y + dy[i], nx = x + dx[i];
				if (ny >= 0 && ny < h && nx >= 0 && nx < w && grid[y][x] >= grid[ny][nx]) {
					ok = false;
					break;
				}
			}
			if (ok) {
				res += grid[y][x] + 1;
			}
		}
	}

	cout << res << endl;

	return 0;
}
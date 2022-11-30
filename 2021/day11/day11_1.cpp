#include <bits/stdc++.h>
using namespace std;

const int dy[8] = {1, 1, 1, 0, 0, -1, -1, -1};
const int dx[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int main () {
	char c;
	long tot = 0;
	uint8_t mat[10][10];
	bool flashed[10][10];
	bool someone;
	int ny, nx;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			scanf("%c", &c);
			mat[i][j] = c - '0';
		}
		scanf("%*c");
	}

	for (int i = 0; i < 100; i++) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				mat[y][x]++;		
			}
		}
		memset((int*)flashed, 0, 100);

		someone = true;
		while (someone) {
			someone = false;
			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {
					if (!flashed[y][x] && mat[y][x] > 9) {
						someone = true;
						flashed[y][x] = true;
						tot++;
						for (int k = 0; k < 8; k++) {
							ny = y + dy[k], nx = x + dx[k];
							if (ny >= 0 && ny < 10 && nx >= 0 && nx < 10) {
								mat[ny][nx]++;
							}
						}
					}
				}
			}
		}
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				if (flashed[y][x]) mat[y][x] = 0;
			}
		}
	}

	cout << tot << endl;
	return 0;
}
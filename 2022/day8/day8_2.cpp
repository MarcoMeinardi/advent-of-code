#include <bits/stdc++.h>
using namespace std;

int main () {
	string line;
	vector <string> grid;

	while (cin >> line) {
		grid.push_back(line);
	}

	int n = (int)grid.size(), m = (int)grid[0].size();
	int res = 0;

	const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

	for (int y = 1; y < n - 1; y++) {
		for (int x = 1; x < m - 1; x++) {
			int view_score = 1;
			for (int i = 0; i < 4; i++) {
				int view = 1;
				while (true) {
					int ny = y + dy[i] * view, nx = x + dx[i] * view;
					if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
						view--;
						break;
					} else if (grid[ny][nx] >= grid[y][x]) break;
					view++;
				}
				view_score *= view;
			}

			res = max(res, view_score);
		}
	}

	cout << res << endl;
}

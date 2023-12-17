#include <bits/stdc++.h>
using namespace std;

const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, -1, 0, 1};

int main ()
{
	vector<vector<int>> grid;
	string line;

	while (cin >> line) {
		vector<int> row;
		for (char c : line) {
			row.push_back(c - '0');
		}
		grid.push_back(std::move(row));
	}

	size_t n = grid.size();
	size_t m = grid[0].size();

	vector<vector<vector<vector<int>>>> dp(n,
		vector<vector<vector<int>>>(m,
			vector<vector<int>>(10,
				vector<int>(4, numeric_limits<int>::max())
			)
		)
	);
	dp[0][0][0][0] = 0;
	dp[0][0][0][3] = 0;

	queue<tuple<size_t, size_t, size_t, int>> q;
	q.emplace(0, 0, 0, 0);
	q.emplace(0, 0, 3, 0);

	while (!q.empty()) {
		size_t ny, nx;
		auto [y, x, d, s] = q.front();
		q.pop();

		for (size_t i = 0; i < 4; i++) {
			if (i == 2) continue;
			size_t nd = (d + i) % 4;
			ny = y + dy[nd], nx = x + dx[nd];
			if (ny >= n || nx >= m) continue;
			if (i == 0) {
				if (s == 9) continue;
				if (dp[ny][nx][s + 1][d] > dp[y][x][s][d] + grid[ny][nx]) {
					dp[ny][nx][s + 1][d] = dp[y][x][s][d] + grid[ny][nx];
					q.emplace(ny, nx, d, s + 1);
				}
			} else {
				if (s < 3) continue;
				if (dp[ny][nx][0][nd] > dp[y][x][s][d] + grid[ny][nx]) {
					dp[ny][nx][0][nd] = dp[y][x][s][d] + grid[ny][nx];
					q.emplace(ny, nx, nd, 0);
				}
			}
		}
	}

	int res = numeric_limits<int>::max();
	for (int step = 3; step < 10; step++) {
		for (int dir = 0; dir < 4; dir++) {
			res = min(res, dp[n - 1][m - 1][step][dir]);
		}
	}
	cout << res << endl;
}

#include <bits/stdc++.h>
using namespace std;

#define COMPRESS(y, x) ((y << 32) | x)
#define DECOMPRESS(yx) make_pair(yx >> 32, yx & 0xffffffff)

int main ()
{
	vector<string> grid;
	string line;
	int64_t sy = -1, sx;
	while (cin >> line) {
		for (int64_t i = 0; i < (int64_t)line.size(); i++) {
			if (line[i] == 'S') {
				assert(sy == -1);
				sy = (int64_t)grid.size();
				sx = i;
				line[i] = '.';
			}
		}
		grid.push_back(line);
	}
	assert(sy != -1);

	unordered_set<int64_t> todo;
	todo.insert(COMPRESS(sy, sx));

	int64_t n = (int64_t)grid.size(), m = (int64_t)grid[0].size();
	for (int i = 0; i < 64; i++) {
		unordered_set<int64_t> next;
		for (int64_t coords : todo) {
			auto [y, x] = DECOMPRESS(coords);
			for (auto [dy, dx] : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
				int64_t ny = y + dy, nx = x + dx;
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
				if (grid[ny][nx] == '#') continue;
				next.insert(COMPRESS(ny, nx));
			}
		}
		todo = std::move(next);
	}

	cout << todo.size() << endl;
}

#include <bits/stdc++.h>
using namespace std;

#define COMPRESS(y, x) (((y + (1 << 30)) << 32) | (x + (1 << 30)))
#define DECOMPRESS(yx) make_pair((yx >> 32) - (1 << 30), (yx & 0xffffffff) - (1 << 30))

int64_t n, m;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int64_t explore(vector<string>& grid, int64_t n_steps, int64_t sy, int64_t sx)
{
	assert(n_steps >= 0);
	unordered_set<int64_t> todo;
	todo.insert(COMPRESS(sy, sx));

	int64_t n = (int64_t)grid.size(), m = (int64_t)grid[0].size();
	for (int step = 0; step < n_steps; step++) {
		unordered_set<int64_t> next;
		for (int64_t coords : todo) {
			auto [y, x] = DECOMPRESS(coords);
			for (int i = 0; i < 4; i++) {
				int64_t ny = y + dy[i], nx = x + dx[i];
				if (grid[(ny % n + n) % n][(nx % m + m) % m] == '#') continue;
				next.insert(COMPRESS(ny, nx));
			}
		}
		todo = std::move(next);
	}

	return (int64_t)todo.size();
}

int main ()
{
	vector<string> grid;
	string line;
	int64_t sy = -1, sx = -1;
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
	assert(sy == sx);

	n = (int64_t)grid.size(), m = (int64_t)grid[0].size();
	assert(n == m);

	int64_t max_steps = 26501365;
	int64_t mod_steps = max_steps % n;

	int64_t one = explore(grid, mod_steps, sy, sx);
	int64_t two = explore(grid, mod_steps + n, sy, sx);
	int64_t three = explore(grid, mod_steps + 2 * n, sy, sx);

	int64_t diff21 = two - one;
	int64_t diff32 = three - two;
	int64_t diff_diff = diff32 - diff21;

	int64_t a = diff_diff / 2;
	int64_t b = diff21 - 3 * a;
	int64_t c = one - a - b;

	function<int64_t(int64_t)> f = [=] (int64_t x) {
		return a * x * x + b * x + c;
	};

	int64_t tot = f(max_steps / n + (max_steps % n != 0));

	cout << tot << endl;
}

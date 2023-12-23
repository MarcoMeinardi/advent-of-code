#include <bits/stdc++.h>
using namespace std;

struct brick_t {
	size_t id;
	int x1, y1, z1;
	int x2, y2, z2;

	brick_t (size_t id, int x1, int y1, int z1, int x2, int y2, int z2) :
		id(id), x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2)
	{
		assert(x1 <= x2 && y1 <= y2 && z1 <= z2);
		assert(z1 > 0);
	}

	void place(vector<vector<vector<size_t>>>& grid)
	{
		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) {
				for (int z = z1; z <= z2; z++) {
					assert(grid[x][y][z] == 0);
					grid[x][y][z] = id;
				}
			}
		}
	}

	void remove(vector<vector<vector<size_t>>>& grid)
	{
		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) {
				for (int z = z1; z <= z2; z++) {
					assert(grid[x][y][z] == id);
					grid[x][y][z] = 0;
				}
			}
		}
	}

	bool can_move_down(vector<vector<vector<size_t>>>& grid)
	{
		if (z1 == 1) {
			return false;
		}
		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) {
				for (int z = z1; z <= z2; z++) {
					if (grid[x][y][z - 1] != 0 && grid[x][y][z - 1] != id) {
						return false;
					}
				}
			}
		}
		return true;
	}

	bool try_move(vector<vector<vector<size_t>>>& grid)
	{
		bool moved = false;
		while (can_move_down(grid)) {
			moved = true;
			remove(grid);
			z1--;
			z2--;
			place(grid);
		}

		return moved;
	}

	void find_supporters(vector<vector<vector<size_t>>>& grid, vector<set<size_t>>& supporters_of)
	{
		if (z1 == 1) return;
		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) {
				for (int z = z1; z <= z2; z++) {
					if (grid[x][y][z - 1] != 0 && grid[x][y][z - 1] != id) {
						supporters_of[id].insert(grid[x][y][z - 1]);
					}
				}
			}
		}
	}
};

int main ()
{
	vector<brick_t> bricks;
	string line;

	int max_x = 0, max_y = 0, max_z = 0;
	size_t max_id = 0;
	while (getline(cin, line)) {
		int x1, y1, z1, x2, y2, z2;
		sscanf(line.c_str(), "%d,%d,%d~%d,%d,%d", &x1, &y1, &z1, &x2, &y2, &z2);
		bricks.emplace_back(++max_id, x1, y1, z1, x2, y2, z2);
		max_x = max(max_x, max(x1, x2));
		max_y = max(max_y, max(y1, y2));
		max_z = max(max_z, max(z1, z2));
	}

	vector<vector<vector<size_t>>> grid(max_x + 1, vector<vector<size_t>>(max_y + 1, vector<size_t>(max_z + 1, 0)));

	for (brick_t& brick : bricks) {
		brick.place(grid);
	}

	bool something_changed;
	do {
		something_changed = false;
		for (brick_t& brick : bricks) {
			something_changed |= brick.try_move(grid);
		}
	} while (something_changed);

	vector<set<size_t>> supporters_of(bricks.size() + 1);
	for (brick_t& brick : bricks) {
		brick.find_supporters(grid, supporters_of);
	}

	int tot = 0;

	for (size_t id1 = 1; id1 <= max_id; id1++) {
		vector<bool> falling(max_id + 1, false);
		falling[id1] = true;
		do {
			something_changed = false;
			for (size_t id2 = 1; id2 <= max_id; id2++) {
				if (falling[id2]) continue;
				if (supporters_of[id2].empty()) continue;
				if (all_of(supporters_of[id2].begin(), supporters_of[id2].end(), [&] (size_t id3) { return falling[id3]; })) {
					falling[id2] = true;
					something_changed = true;
				}
			}
		} while (something_changed);
		tot += accumulate(falling.begin(), falling.end(), 0) - 1;

	}

	cout << tot << endl;
}

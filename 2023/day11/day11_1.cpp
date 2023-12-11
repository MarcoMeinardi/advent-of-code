#include <bits/stdc++.h>
using namespace std;

int get_dist(pair<int, int>& a, pair<int, int>& b, vector<bool>& is_empty_row, vector<bool>& is_empty_col)
{
	auto [ay, ax] = a;
	auto [by, bx] = b;
	int res = abs(ay - by) + abs(ax - bx);

	for (int y = min(ay, by) + 1; y < max(ay, by); y++) {
		res += is_empty_row[y];
	}
	for (int x = min(ax, bx) + 1; x < max(ax, bx); x++) {
		res += is_empty_col[x];
	}
	
	return res;
}

int main ()
{
	vector<vector<bool>> universe;
	string line;
	vector<pair<int, int>> galaxies;

	while (cin >> line) {
		universe.push_back(vector<bool>(line.size()));
		for (size_t i = 0; i < line.size(); i++) {
			if (line[i] == '#') {
				galaxies.emplace_back(universe.size() - 1, i);
				universe.back()[i] = true;
			} else {
				universe.back()[i] = false;
			}
		}
	}

	vector<bool> is_empty_row(universe.size());
	vector<bool> is_empty_col(universe[0].size());
	for (size_t y = 0; y < universe.size(); y++) {
		bool empty = true;
		for (size_t x = 0; x < universe[y].size(); x++) {
			if (universe[y][x]) {
				empty = false;
				break;
			}
		}
		is_empty_row[y] = empty;
	}
	for (size_t x = 0; x < universe[0].size(); x++) {
		bool empty = true;
		for (size_t y = 0; y < universe.size(); y++) {
			if (universe[y][x]) {
				empty = false;
				break;
			}
		}
		is_empty_col[x] = empty;
	}

	int tot = 0;
	for (size_t i = 0; i < galaxies.size(); i++) {
		for (size_t j = i + 1; j < galaxies.size(); j++) {
			tot += get_dist(galaxies[i], galaxies[j], is_empty_row, is_empty_col);
		}
	}

	cout << tot << endl;
}

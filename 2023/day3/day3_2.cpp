#include <bits/stdc++.h>
using namespace std;

const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int n, m;

tuple<int, int, int> get_num(string& line, int x)
{
	while (x >= 0 && isdigit(line[x])) {
		x--;
	}
	x++;
	int first_x = x;
	while (x < m && isdigit(line[x])) {
		x++;
	}
	return {stoi(&line[first_x]), first_x, x};
}

int calc_gear(vector<string> &mat, int y, int x)
{
	vector<tuple<int, int, int, int>> nums;
	for (int i = 0; i < 8; i++) {
		int ny = y + dy[i], nx = x + dx[i];
		if (ny < n && ny >= 0 && nx < m && nx >= 0) {
			if (isdigit(mat[ny][nx])) {
				auto [num, first_x, last_x] = get_num(mat[ny], nx);
				bool ok = true;
				for (auto [_, oy, __, ox] : nums) {
					if (oy == ny && ox >= first_x) {
						ok = false;
						break;
					}
				}
				if (ok) {
					nums.push_back({num, ny, first_x, last_x});
				}
			}
		}
	}
	if (nums.size() == 2) {
		return get<0>(nums[0]) * get<0>(nums[1]);
	}
	return 0;
}

int main ()
{
	vector<string> mat;
	string line;
	while (cin >> line) {
		mat.push_back(line);
	}
	n = mat.size();
	m = mat[0].size();

	int tot = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (mat[y][x] == '*') {
				tot += calc_gear(mat, y, x);
			}
		}
	}
	cout << tot << endl;
}

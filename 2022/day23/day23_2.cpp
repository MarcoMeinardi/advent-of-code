#include <bits/stdc++.h>
#include <limits>
using namespace std;

struct point_t {
	int y;
	int x;

	point_t() = default;
	point_t(int y, int x): y(y), x(x) {}
};

bool operator < (const point_t& a, const point_t& b) {
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}
bool operator == (const point_t& a, const point_t& b) {
	return a.y == b.y && a.x == b.x;
}

set<point_t> points;
const int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
const int ddy[4][3] = {{-1, -1, -1}, {1, 1, 1}, {-1, 0, 1}, {-1, 0, 1}};
const int ddx[4][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, -1, -1}, {1, 1, 1}};
const int Dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, Dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool round() {
	static int round_n = -1;
	round_n++;

	map<point_t, pair<bool, point_t>> next_points;

	for (const point_t& point : points) {
		bool any_neig = false;
		for (int i = 0; i < 8; i++) {
			int ny = point.y + Dy[i], nx = point.x + Dx[i];
			if (points.find(point_t(ny, nx)) != points.end()) {
				any_neig = true;
				break;
			}
		}
		if (!any_neig) continue;

		for (int i = 0; i < 4; i++) {
			bool any_monkey = false;
			for (int j = 0; j < 3; j++) {
				int ny = point.y + ddy[(i + round_n) % 4][j], nx = point.x + ddx[(i + round_n) % 4][j];
				if (points.find(point_t(ny, nx)) != points.end()) {
					any_monkey = true;
					break;
				}
			}

			if (!any_monkey) {
				point_t new_point = point_t(point.y + dy[(i + round_n) % 4], point.x + dx[(i + round_n) % 4]);
				if (next_points.find(new_point) == next_points.end()) {
					next_points[new_point] = make_pair(true, point);
				} else {
					next_points[new_point].first = false;
				}
				break;
			}
		}
	}

	bool any_move = false;
	for (auto [new_point, pp] : next_points) {
		auto [ok, old_point] = pp;
		if (!ok) continue;

		points.erase(old_point);
		points.insert(new_point);
		any_move = true;
	}

	return any_move;
}

int main () {
	string line;
	for (int y = 0; cin >> line; y++) {
		for (int x = 0; x < (int)line.size(); x++) {
			if (line[x] == '#') {
				points.emplace(y, x);
			}
		}
	}

	int res;
	for (res = 1; round(); res++);

	cout << res << endl;
}

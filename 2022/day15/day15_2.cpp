#include <bits/stdc++.h>
using namespace std;

struct point_t {
	int y;
	int x;

	point_t() = default;
	point_t(int y, int x) : y(y), x(x) {}
	point_t(const point_t& other) : y(other.y), x(other.x) {}
};

bool operator < (const point_t& a, const point_t& b) {
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}
bool operator == (const point_t& a, const point_t& b) {
	return a.y == b.y && a.x == b.x;
}

int dist(const point_t& a, const point_t& b) {
	return abs(a.y - b.y) + abs(a.x - b.x);
}

bool read_line(point_t& sensor, point_t& beacon) {
	string line;
	if (!getline(cin, line)) return false;

	char* data = line.data();
	int* points[] = {&sensor.x, &sensor.y, &beacon.x, &beacon.y};
	int ind = 0;
	data = strtok(data, "=");
	do {
		data = strtok(NULL, ",:");
		*points[ind++] = atoi(data);
	} while (strtok(NULL, "="));

	return true;
}

int main () {
	vector <pair <point_t, point_t>> sensors;

	point_t sensor;
	point_t beacon;
	while (read_line(sensor, beacon)) {
		sensors.emplace_back(sensor, beacon);
	}

	int min_x = numeric_limits<int>::max(), max_x = numeric_limits<int>::min();

	for (auto [sensor, beacon] : sensors) {
		min_x = min(min_x, sensor.x - dist(sensor, beacon));
		max_x = max(max_x, sensor.x + dist(sensor, beacon));
	}

	int64_t resy = -1, resx = -1;
	for (int y = 0; y <= 4000000 && resy == -1; y++) {
		set <pair <int, int>> intervals;
		for (auto [sensor, beacon] : sensors) {
			int total_distance = dist(sensor, beacon);
			int dy = abs(sensor.y - y);
			int dx = total_distance - dy;
			if (dx < 0) continue;
			intervals.emplace(sensor.x - dx, sensor.x + dx);
		}

		int pos = intervals.begin()->second + 1;
		for (auto [a, b] : intervals) {
			if (a > pos) {
				assert(a == pos + 1);
				resy = y, resx = pos;
				break;
			}
			pos = max(pos, b + 1);
		}
	}

	assert(resy != -1);
	cout << (resx * 4000000 + resy) << endl;
}

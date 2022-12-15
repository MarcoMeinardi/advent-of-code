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

	int res = 0;
	for (int x = min_x; x <= max_x; x++) {
		point_t p = point_t(2000000, x);
		bool covered = false;
		bool in_range = false;
		for (auto [sensor, beacon] : sensors) {
			if (beacon == p) {
				covered = true;
			}
			if (dist(sensor, p) <= dist(sensor, beacon)) {
				in_range = true;
			}
		}
		res += !covered && in_range;
	}

	cout << res << endl;
}

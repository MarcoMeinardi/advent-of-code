#include <bits/stdc++.h>
using namespace std;

const int dy[] = {0, 1, 0, -1};
const int dx[] = {1, 0, -1, 0};

int64_t shoelace(vector<pair<int64_t, int64_t>>& vertex)
{
	int64_t area = 0;
	for (size_t i = 0; i < vertex.size(); i++) {
		area +=
			vertex[i].second * vertex[(i + 1) % vertex.size()].first -
			vertex[i].first * vertex[(i + 1) % vertex.size()].second;
	}
	return area / 2;
}

int64_t half_perimeter(vector<pair<int64_t, int64_t>>& vertex)
{
	int64_t perim = 0;
	for (size_t i = 0; i < vertex.size(); i++) {
		perim += abs(vertex[i].first - vertex[(i + 1) % vertex.size()].first) +
			abs(vertex[i].second - vertex[(i + 1) % vertex.size()].second);
	}
	return perim / 2;
}

int main ()
{
	vector<pair<int64_t, int64_t>> vertex;
	__attribute__((unused)) char dir_c;
	int dir;
	__attribute__((unused)) int steps;
	string color_str;
	int64_t rsteps;

	int64_t y = 0, x = 0;
	vertex.emplace_back(y, x);

	while (cin >> dir_c >> steps >> color_str) {
		rsteps = stoull(color_str.substr(2, 5), nullptr, 16);
		dir = stoull(color_str.substr(7, 1), nullptr, 16);

		y += dy[dir] * rsteps;
		x += dx[dir] * rsteps;
		vertex.emplace_back(y, x);
	}

	cout << (shoelace(vertex) + half_perimeter(vertex) + 1) << endl;
}

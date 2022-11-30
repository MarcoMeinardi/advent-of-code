#include <bits/stdc++.h>
using namespace std;

int hash_point(int y, int x) {
	return y * 10000 + x;
}

int main () {
	vector <array <int, 2>> points;
	set <int> uniques;
	int w = 0, h = 0;
	int ax = 0;
	int bound;
	int a, b;
	char foo[6];

	while (scanf("%d%*c%d", &a, &b) == 2) {
		points.push_back({a, b});
	}

	while (scanf("%s %s %c%*c%d", foo, foo, (char*)&ax, &bound) == 4) {
		ax = ax - 'x';
		for (array <int, 2>& point : points) {
			if (point[ax] > bound) {
				point[ax] = 2 * bound - point[ax];
			}
		}
	}

	for (array <int, 2>& point : points) {
		w = max(w, point[0]), h = max(h, point[1]);
		uniques.insert(hash_point(point[1], point[0]));
	}

	for (int y = 0; y <= h; y++) {
		for (int x = 0; x <= w; x++) {
			if (uniques.find(hash_point(y, x)) != uniques.end()) {
				cout << "█";
			} else {
				cout << " ";
			}
		}
		cout << endl;
	}
	// PERCGJPB

	return 0;
}
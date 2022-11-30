#include <bits/stdc++.h>
using namespace std;

int hash_point(int y, int x) {
	return y * 10000 + x;
}

int main () {
	vector <array <int, 2>> points;
	set <int> uniques;
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
		break; // just the first one
	}

	for (array <int, 2>& point : points) {
		uniques.insert(hash_point(point[1], point[0]));
	}
	cout << uniques.size() << endl;
	return 0;
}
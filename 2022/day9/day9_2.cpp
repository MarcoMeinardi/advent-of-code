#include <bits/stdc++.h>
using namespace std;

int dist(pair <int, int> a, pair <int, int> b) {
	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main () {
	vector <pair <int, int>> knots(10, make_pair(0, 0));
	set <pair <int, int>> visited;
	visited.emplace(0, 0);

	int dy[0x80], dx[0x80];
	dy['R'] =  0; dx['R'] =  1;
	dy['U'] = -1; dx['U'] =  0;
	dy['L'] =  0; dx['L'] = -1;
	dy['D'] =  1; dx['D'] =  0;

	char dir;
	int n;
	while (cin >> dir >> n) {
		while (n--) {
			knots[0].first += dy[(size_t)dir];
			knots[0].second += dx[(size_t)dir];
			
			for (int i = 1; i < 10; i++) {
				while (dist(knots[i], knots[i - 1]) >= 2) {
					if (knots[i].first < knots[i - 1].first) knots[i].first++;
					if (knots[i].first > knots[i - 1].first) knots[i].first--;
					if (knots[i].second < knots[i - 1].second) knots[i].second++;
					if (knots[i].second > knots[i - 1].second) knots[i].second--;
				}
			}
			visited.emplace(knots.back());
		}
	}

	cout << visited.size() << endl;
}

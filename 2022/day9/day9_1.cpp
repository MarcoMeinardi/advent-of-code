#include <bits/stdc++.h>
using namespace std;

int dist(int hy, int hx, int ty, int tx) {
	return sqrt((hy - ty) * (hy - ty) + (hx - tx) * (hx - tx));
}

int main () {
	int hy = 0, hx = 0, ty = 0, tx = 0;
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
			hy += dy[(size_t)dir];
			hx += dx[(size_t)dir];
			
			if (dist(hy, hx, ty, tx) >= 2) {
				if (ty < hy) ty++;
				if (ty > hy) ty--;
				if (tx < hx) tx++;
				if (tx > hx) tx--;
				visited.emplace(ty, tx);
			}
		}
	}

	cout << visited.size() << endl;
}

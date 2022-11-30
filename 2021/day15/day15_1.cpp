#include <bits/stdc++.h>
using namespace std;

#define Y(coord) (coord / n)
#define X(coord) (coord % n)
#define h(coord) (abs(Y(coord) - n) + abs(X(coord) - m))
#define GOAL (n - 1) * n + (m - 1)
#define comp [&] (int a, int b) {return f[a] > f[b];}

const int dy[4] = {0, 0, 1, -1};
const int dx[4] = {1, -1, 0, 0};

int main () {
	vector <int> board;
	vector <int> prev, g, f;
	vector <int> heap;
	set <int> vis;
	int curr, next;
	int n = 0, m = 0;
	int tot = 0;
	int maybe_g;
	string line;

	while(cin >> line) {
		m = line.size();
		for (int i = 0; i < m; i++) {
			board.push_back(line[i] & 0xf);
		}
		n++;
	}

	prev.resize(n * m);
	g.resize(n * m);
	f.resize(n * m);
	for (int i = 1; i < n * m; i++) {
		prev[i] = -1;
		g[i] = 1e9 + 5;
		f[i] = 1e9 + 5;
	}
	g[0] = 0;
	f[0] = h(0);

	heap.push_back(0);
	vis.insert(0);

	while(!heap.empty()) {
		pop_heap(heap.begin(), heap.end(), comp);
		curr = heap.back();
		heap.pop_back();
		vis.erase(curr);

		if (curr == GOAL) {
			while(curr) {
				tot += board[curr];
				curr = prev[curr];
			}

			cout << tot << endl;
			return 0;
		}

		for (int i = 0; i < 4; i++) {
			next = curr + n * dy[i] + dx[i];
			if (Y(next) < 0 || Y(next) >= n || X(next) < 0 || (dy[i] == 0 && Y(next) != Y(curr))) continue;
			maybe_g = g[curr] + board[next];

			if (maybe_g < g[next]) {
				prev[next] = curr;
				g[next] = maybe_g;
				f[next] = maybe_g + h(next);

				if (vis.find(next) == vis.end()) {
					vis.insert(next);
					heap.push_back(next);
					push_heap(heap.begin(), heap.end(), comp);
				}
			}
		}
	}

	assert(false);
}
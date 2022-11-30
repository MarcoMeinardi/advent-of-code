#include <bits/stdc++.h>
using namespace std;

#define Y(coord) (coord / n5)
#define X(coord) (coord % m5)
#define h(coord) (abs(Y(coord) - n5) + abs(X(coord) - m5))
#define GOAL (n5 - 1) * n5 + (m5 - 1)
#define comp [&] (int a, int b) {return f[a] > f[b];}

const int dy[4] = {0, 0, 1, -1};
const int dx[4] = {1, -1, 0, 0};

int main () {
	vector <int> board;
	vector <int> big_board;
	vector <int> prev, g, f;
	vector <int> heap;
	set <int> vis;
	int curr, next;
	int n = 0, m = 0;
	int n5, m5;
	int tot = 0;
	int maybe_g;
	string line;

	while(cin >> line) {
		m = line.size();
		for (int i = 0; i < m; i++) {
			board.push_back((line[i] & 0xf));
		}
		n++;
	}
	n5 = n * 5, m5 = m * 5;

	prev.resize(n5 * m5);
	g.resize(n5 * m5);
	f.resize(n5 * m5);
	big_board.resize(n5 * m5);
	for (int i = 1; i < n5 * m5; i++) {
		prev[i] = -1;
		g[i] = 1e9 + 5;
		f[i] = 1e9 + 5;
		big_board[i] = (board[Y(i) % n * n + i % m] + Y(i) / n + X(i) / m - 1) % 9 + 1;
	}
	big_board[0] = board[0];
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
				tot += big_board[curr];
				curr = prev[curr];
			}

			cout << tot << endl;
			return 0;
		}

		for (int i = 0; i < 4; i++) {
			next = curr + n5 * dy[i] + dx[i];
			if (Y(next) < 0 || Y(next) >= n5 || X(next) < 0 || (dy[i] == 0 && Y(next) != Y(curr))) continue;
			maybe_g = g[curr] + big_board[next];

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
#include <bits/stdc++.h>
using namespace std;

const int dy[4] = {0, 1, 0, -1}, dx[4] = {1, 0, -1, 0};

int read_int(char*& str) {
	int res = 0;
	while (isdigit(*str)) {
		res *= 10;
		res += *str - '0';
		str++;
	}
	return res;
}

int main () {
	string line;
	string commands;
	vector<string> grid;
	int n = 0, m = 0;

	while (getline(cin, line) && !line.empty()) {
		if (isdigit(line[0])) break;
		grid.push_back(line);
		n++;
		m = max(n, (int)line.size());
	}
	getline(cin, commands);

	vector<pair<int, int>> rows(n);
	vector<pair<int, int>> coloumns(m);
	for (int i = 0; i < n; i++) {
		rows[i].first = grid[i].find_first_not_of(' ');
		rows[i].second = grid[i].find_last_not_of(' ');
	}

	for (int i = 0; i < m; i++) {
		int start = 0;
		while (start < n && ((int)grid[start].size() < i || grid[start][i] == ' ')) {
			start++;
		}
		int finish = start + 1;
		while (finish < n && (int)grid[finish].size() > i && grid[finish][i] != ' ') {
			finish++;
		}
		finish--;
		coloumns[i] = make_pair(start, finish);
	}

	int y = 0, x = rows[0].first;
	int dir = 0;

	char* cmd = commands.data();
	while (true) {
		int q = read_int(cmd);
		while (q--) {
			int ny = y + dy[dir], nx = x + dx[dir];
			if      (dir == 0 && x == rows[y].second) nx = rows[y].first;
			else if (dir == 2 && x == rows[y].first) nx = rows[y].second;
			else if (dir == 1 && y == coloumns[x].second) ny = coloumns[x].first;
			else if (dir == 3 && y == coloumns[x].first) ny = coloumns[x].second;

			if (grid[ny][nx] == '#') {
				break;
			} else {
				assert(grid[ny][nx] == '.');
				y = ny, x = nx;
			}
		}
		if (*cmd == 'R') dir = (dir + 1) % 4;
		else if (*cmd == 'L') dir = (dir + 3) % 4;
		else { assert(*cmd == '\0'); break; }
		cmd++;
	}

	int res = 1000 * (y + 1) + 4 * (x + 1) + dir;
	cout << res << endl;
}

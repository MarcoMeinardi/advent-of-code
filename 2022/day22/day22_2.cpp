#include <bits/stdc++.h>
using namespace std;

#define CUBE_SIDE 50
enum dir_t {RIGHT, DOWN, LEFT, UP};

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
	int n = 0;

	while (getline(cin, line) && !line.empty()) {
		if (isdigit(line[0])) break;
		grid.push_back(line);
		n++;
	}
	getline(cin, commands);

	int y = 0, x = grid[0].find_first_not_of(' ');
	int dir = 0;

	char* cmd = commands.data();
	while (true) {
		int q = read_int(cmd);
		while (q--) {
			int ny = y + dy[dir], nx = x + dx[dir];

			if (dir == RIGHT && x % CUBE_SIDE == CUBE_SIDE - 1) {
				if (y / CUBE_SIDE == 0 && x / CUBE_SIDE == 2) {
					ny = CUBE_SIDE * 2 + CUBE_SIDE - y - 1;
					nx = CUBE_SIDE * 2 - 1;
					if (grid[ny][nx] != '#') dir = LEFT;
				} else if (y / CUBE_SIDE == 1 && x / CUBE_SIDE == 1) {
					ny = CUBE_SIDE - 1;
					nx = CUBE_SIDE * 2 + (y - CUBE_SIDE);
					if (grid[ny][nx] != '#') dir = UP;
				} else if (y / CUBE_SIDE == 2 && x / CUBE_SIDE == 1) {
					ny = CUBE_SIDE - (y - CUBE_SIDE * 2) - 1;
					nx = CUBE_SIDE * 3 - 1;
					if (grid[ny][nx] != '#') dir = LEFT;
				} else if (y / CUBE_SIDE == 3 && x / CUBE_SIDE == 0) {
					ny = CUBE_SIDE * 3 - 1;
					nx = CUBE_SIDE + y - CUBE_SIDE * 3;
					if (grid[ny][nx] != '#') dir = UP;
				}
			}
			else if (dir == LEFT && x % CUBE_SIDE == 0) {
				if (y / CUBE_SIDE == 0 && x / CUBE_SIDE == 1) {
					ny = CUBE_SIDE * 2 + CUBE_SIDE - y - 1;
					nx = 0;
					if (grid[ny][nx] != '#') dir = RIGHT;
				} else if (y / CUBE_SIDE == 1 && x / CUBE_SIDE == 1) {
					ny = CUBE_SIDE * 2;
					nx = y - CUBE_SIDE;
					if (grid[ny][nx] != '#') dir = DOWN;
				} else if (y / CUBE_SIDE == 2 && x / CUBE_SIDE == 0) {
					ny = CUBE_SIDE - (y - CUBE_SIDE * 2) - 1;
					nx = CUBE_SIDE;
					if (grid[ny][nx] != '#') dir = RIGHT;
				} else if (y / CUBE_SIDE == 3 && x / CUBE_SIDE == 0) {
					ny = 0;
					nx = CUBE_SIDE + (y - CUBE_SIDE * 3);
					if (grid[ny][nx] != '#') dir = DOWN;
				}
			}
			else if (dir == DOWN && y % CUBE_SIDE == CUBE_SIDE - 1) {
				if (y / CUBE_SIDE == 0 && x / CUBE_SIDE == 2) {
					ny = CUBE_SIDE + (x - CUBE_SIDE * 2);
					nx = CUBE_SIDE * 2 - 1;
					if (grid[ny][nx] != '#') dir = LEFT;
				} else if (y / CUBE_SIDE == 2 && x / CUBE_SIDE == 1) {
					ny = CUBE_SIDE * 3 + (x - CUBE_SIDE);
					nx = CUBE_SIDE - 1;
					if (grid[ny][nx] != '#') dir = LEFT;
				} else if (y / CUBE_SIDE == 3 && x / CUBE_SIDE == 0) {
					ny = 0;
					nx = CUBE_SIDE * 2 + x;
					if (grid[ny][nx] != '#') dir = DOWN;
				}
			}
			else if (dir == 3 && y % CUBE_SIDE == 0) {
				if (y / CUBE_SIDE == 0 && x / CUBE_SIDE == 1) {
					ny = CUBE_SIDE * 3 + (x - CUBE_SIDE);
					nx = 0;
					if (grid[ny][nx] != '#') dir = RIGHT;
				} else if (y / CUBE_SIDE == 0 && x / CUBE_SIDE == 2) {
					ny = CUBE_SIDE * 4 - 1;
					nx = x - CUBE_SIDE * 2;
					if (grid[ny][nx] != '#') dir = UP;
				} else if (y / CUBE_SIDE == 2 && x / CUBE_SIDE == 0) {
					ny = CUBE_SIDE + x;
					nx = CUBE_SIDE;
					if (grid[ny][nx] != '#') dir = RIGHT;
				}
			}

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

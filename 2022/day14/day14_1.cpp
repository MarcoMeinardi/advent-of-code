#include <bits/stdc++.h>
using namespace std;

#define EMPTY 0
#define ROCK 1
#define SAND 2
int grid[1000][1000];
int lowest = 0;

void build_wall(char* instr) {
	int py = -1, px = -1;
	while (true) {
		char* comma = strchr(instr, ',');
		*comma = '\0';
		int x = atoi(instr);
		instr = comma + 1;
		char* space = strchr(instr, ' ');
		if (space) *space = '\0';
		int y = atoi(instr);
		lowest = max(lowest, y);
		
		if (py != -1) {
			if (py != y) {
				while (py < y) {
					grid[py][px] = ROCK;
					py++;
				}
				while (y < py) {
					grid[py][px] = ROCK;
					py--;
				}
			} else {
				while (px < x) {
					grid[py][px] = ROCK;
					px++;
				}
				while (x < px) {
					grid[py][px] = ROCK;
					px--;
				}
			}
		}
		if (!space) {
			grid[y][x] = ROCK;
			break;
		}
		py = y, px = x;
		instr = space + 4;
	}
}

bool put_sand() {
	int y = 0, x = 500;
	while (y < lowest) {
		if (grid[y + 1][x] == EMPTY) {
			y++;
		} else if (grid[y + 1][x - 1] == EMPTY) {
			y++, x--;
		} else if (grid[y + 1][x + 1] == EMPTY) {
			y++, x++;
		} else {
			grid[y][x] = SAND;
			return true;
		}
	}
	return false;
}

int main () {
	string line;
	while (getline(cin, line)) {
		build_wall(line.data());
	}

	int res = 0;
	while (put_sand()) res++;

	cout << res << endl;
}

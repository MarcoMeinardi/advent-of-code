#include <bits/stdc++.h>
using namespace std;

struct board {
	int mat[5][5];
	bool marked[5][5];
	int unmarked_sum;
	bool success;

	board () {
		unmarked_sum = 0;
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if(!(cin >> mat[y][x])) {
					success = false;
					return;
				}
				marked[y][x] = false;
				unmarked_sum += mat[y][x];
			}
		}
		success = true;
	};

	bool check_win (int y, int x) {
		for (int y = 0, x; y < 5; y++) {
			for (x = 0; x < 5; x++) {
				if (!marked[y][x]) {
					break;
				}
			}
			if (x == 5) {
				return true;
			}
		}
		for (int x = 0, y; x < 5; x++) {
			for (y = 0; y < 5; y++) {
				if (!marked[y][x]) {
					break;
				}
			}
			if (y == 5) {
				return true;
			}
		}
		return false;
	}

	bool mark_and_check (int num) {
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (mat[y][x] == num) {
					marked[y][x] = true;
					unmarked_sum -= num;
					if (check_win(y, x)) {
						return true;
					}
				}
			}
		}
		return false;
	};
};

int main () {
	vector <struct board*> boards;
	struct board* actual_board;
	vector <int> nums;
	int n;
	char maybe_newline;

	do {
		scanf("%d%c", &n, &maybe_newline);
		nums.push_back(n);
	} while (maybe_newline != '\n');

	do {
		actual_board = new board();
		if (actual_board->success) {
			boards.push_back(actual_board);
		}
	} while (actual_board->success);
	free(actual_board);

	for (int num : nums) {
		for (struct board* board : boards) {
			if (board->mark_and_check(num)) {
				cout << (board->unmarked_sum * num) << endl;
				return 0;
			}
		}
	}

	assert(false);
}
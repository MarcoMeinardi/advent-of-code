#include <bits/stdc++.h>
using namespace std;

int main () {
	short int grid[1000][1000] = {};
	int tot = 0;

	int x1, y1, x2, y2;

	while (scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
		if (x1 == x2) {
			if (y1 > y2) swap (y1, y2);
			for (; y1 <= y2; y1++) {
				tot += grid[x1][y1]++ == 1;
			}
		} else if (y1 == y2) {
			if (x1 > x2) swap (x1, x2);
			for (; x1 <= x2; x1++) {
				tot += grid[x1][y1]++ == 1;
			}
		} else if (abs(x1 - x2) == abs(y1 - y2)) {
			if (x1 < x2) {
				if (y1 < y2) {
					for (; x1 <= x2; x1++, y1++) {
						tot += grid[x1][y1]++ == 1;
					}
				} else {
					for (; x1 <= x2; x1++, y1--) {
						tot += grid[x1][y1]++ == 1;
					}
				}
			} else {
				if (y1 < y2) {
					for (; x2 <= x1; x1--, y1++) {
						tot += grid[x1][y1]++ == 1;
					}
				} else {
					for (; x2 <= x1; x1--, y1--) {
						tot += grid[x1][y1]++ == 1;
					}
				}
			}
		}
	}

	cout << tot << endl;
	return 0;
}
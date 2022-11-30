#include <bits/stdc++.h>
using namespace std;

int main () {
	int x0 = 29, x1 = 73;
	int y0 = -248, y1 = -194;

	// x * (x - 1) / 2 >= x0
	// x^2 - x - 2 * x0 >= 0
	// (1 + sqrt(1 + 8 * x0)) / 2
	int min_x_speed = (1 + sqrt(1 + 8 * x0)) / 2;

	int y, x;
	int act_ys, act_xs;
	int tot = 0;
	for (int ys = y0; ys < -y0; ys++) {
		for (int xs = min_x_speed; xs <= x1; xs++) {
			y = 0, x = 0;
			act_ys = ys, act_xs = xs;
			while (y >= y0 && x <= x1) {
				if (y <= y1 && x >= x0) {
					tot++;
					break;
				}
				y += act_ys--;
				x += max(0, act_xs--);
			}

		}
	}

	cout << tot << endl;
	return 0;
}
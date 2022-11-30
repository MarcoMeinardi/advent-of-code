#include <bits/stdc++.h>
using namespace std;

int main () {
	int x0 = 29, x1 = 73;
	int y0 = -248, y1 = -194;

	double max_speed = -y0 - 1;

	int max_h = max_speed * (max_speed + 1) / 2;
	cout << (int)max_h << endl;
	return 0;
}
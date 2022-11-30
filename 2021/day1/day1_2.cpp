#include <bits/stdc++.h>
using namespace std;

int main () {
	int tot = 0;
	int p_depth[3], depth[3];
	cin >> p_depth[0];
	cin >> p_depth[1];
	cin >> p_depth[2];
	depth[0] = p_depth[1];
	depth[1] = p_depth[2];
	while (cin >> depth[2]) {
		tot += depth[0] + depth[1] + depth[2] > p_depth[0] + p_depth[1] + p_depth[2];
		p_depth[0] = p_depth[1], p_depth[1] = p_depth[2], p_depth[2] = depth[2];
		depth[0] = depth[1], depth[1] = depth[2];
	}
	cout << tot << endl;
	return 0;
}
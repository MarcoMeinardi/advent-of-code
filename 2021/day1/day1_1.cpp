#include <bits/stdc++.h>
using namespace std;

int main () {
	int tot = 0;
	int p_depth, depth;
	cin >> p_depth;
	while (cin >> depth) {
		tot += depth > p_depth;
		p_depth = depth;
	}
	cout << tot << endl;
	return 0;
}

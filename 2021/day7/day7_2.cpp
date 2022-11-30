#include <bits/stdc++.h>
using namespace std;

int main () {
	vector <int> crabs;
	int n;
	int target, tot1 = 0, tot2 = 0;

	while (scanf("%d%*c", &n) == 1) {
		crabs.push_back(n);
	}

	target = floor((double)accumulate(crabs.begin(), crabs.end(), 0) / crabs.size());

	for_each(crabs.begin(), crabs.end(), [&] (int crab) {
		int d1 = abs(crab - target);
		int d2 = abs(crab - (target + 1));
		tot1 += d1 * (d1 + 1) / 2, tot2 += d2 * (d2 + 1) / 2;
	});

	cout << min(tot1, tot2) << endl;

	return 0;
}
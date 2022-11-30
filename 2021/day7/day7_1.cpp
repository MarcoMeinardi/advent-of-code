#include <bits/stdc++.h>
using namespace std;

int main () {
	vector <int> crabs;
	int n;
	int target, tot = 0;

	while (scanf("%d%*c", &n) == 1) {
		crabs.push_back(n);
	}

	sort(crabs.begin(), crabs.end());
	target = crabs[crabs.size() / 2];

	for_each(crabs.begin(), crabs.end(), [&] (int crab) {tot += abs(crab - target);});
	cout << tot << endl;

	return 0;
}
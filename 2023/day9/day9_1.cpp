#include <bits/stdc++.h>
using namespace std;

int main ()
{
	int64_t tot = 0;
	string line;

	while (getline(cin, line)) {
		stringstream ss(line);
		vector<int64_t> vals;
		int64_t x;
		while (ss >> x) {
			vals.push_back(x);
		}

		size_t n = vals.size();
		size_t depth = 1;
		while (!all_of(vals.begin(), vals.end() - depth + 1, [](int64_t x) { return x == 0; })) {
			for (size_t i = 0; i < n - depth; i++) {
				vals[i] = vals[i + 1] - vals[i];
			}
			depth++;
		}

		tot += accumulate(vals.end() - depth, vals.end(), 0);
	}

	cout << tot << endl;
}

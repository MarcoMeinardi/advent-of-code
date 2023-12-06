#include <bits/stdc++.h>
using namespace std;

int main ()
{
	string line;
	vector<uint64_t> times;
	vector<uint64_t> dists;
	string foo;

	getline(cin, line);
	stringstream ss(line);
	ss >> foo;

	uint64_t val;

	while (ss >> val) {
		times.push_back(val);
	}

	getline(cin, line);
	ss = stringstream(line);
	ss >> foo;

	while (ss >> val) {
		dists.push_back(val);
	}
	assert(times.size() == dists.size());

	uint64_t res = 1;
	for (size_t i = 0; i < times.size(); i++) {
		uint64_t good = 0;
		for (uint64_t hold = 0; hold < times[i]; hold++) {
			// dist = hold * (time - hold)
			good += hold * (times[i] - hold) > dists[i];
		}
		res *= good;
	}

	cout << res << endl;
}

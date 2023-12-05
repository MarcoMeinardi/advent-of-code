#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

struct range_t {
	uint64_t destination;
	uint64_t source;
	uint64_t length;
};

int main ()
{
	vector<uint64_t> seeds;
	vector<vector<range_t>> ranges(7);

	string line;
	getline(cin, line);

	stringstream ss(line);
	ss.ignore(0x100, ' ');
	uint64_t seed_val;
	while (ss >> seed_val) {
		seeds.push_back(seed_val);
	}

	getline(cin, line);
	for (int i = 0; i < 7; i++) {
		getline(cin, line);
		while (getline(cin, line) && line.length() > 0) {
			stringstream ss(line);
			range_t range;
			ss >> range.destination >> range.source >> range.length;
			ranges[i].push_back(range);
		}
	}

	uint64_t res = UINT64_MAX;

	for (uint64_t seed : seeds) {
		for (vector<range_t>& range : ranges) {
			for (range_t& r : range) {
				if (r.source <= seed && seed < r.source + r.length) {
					seed = r.destination + seed - r.source;
					break;
				}
			}
		}
		res = min(res, seed);
	}

	cout << res << endl;
}

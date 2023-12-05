#include <bits/stdc++.h>
using namespace std;

struct range_t {
	uint64_t dest_start;
	uint64_t dest_end;
	uint64_t source_start;
	uint64_t source_end;
};

struct seed_range_t {
	uint64_t start;
	uint64_t end;
};

int main ()
{
	queue<seed_range_t> seeds_queue;
	vector<vector<range_t>> ranges(7);

	string line;
	getline(cin, line);

	stringstream ss(line);
	uint64_t val, length;
	ss.ignore(0x100, ' ');
	while (ss >> val >> length) {
		seeds_queue.emplace(val, val + length);
	}

	getline(cin, line);
	for (int i = 0; i < 7; i++) {
		getline(cin, line);
		while (getline(cin, line) && line.length() > 0) {
			stringstream ss(line);
			uint64_t dest, source, length;
			ss >> dest >> source >> length;
			ranges[i].emplace_back(dest, dest + length, source, source + length);
		}
	}


	queue<seed_range_t> next_seeds_queue;

	for (int i = 0; i < 7; i++) {
		while (!seeds_queue.empty()) {
			seed_range_t seed_range = seeds_queue.front();
			seeds_queue.pop();

			bool found = false;
			for (range_t& range : ranges[i]) {
				if (range.source_start <= seed_range.start) {  // seed start after range start
					if (seed_range.start < range.source_end) {  // start inside
						if (seed_range.end <= range.source_end) {  // all inside
							next_seeds_queue.emplace(
								range.dest_start + seed_range.start - range.source_start,
								range.dest_start + seed_range.end - range.source_start
							);
							found = true; break;
						} else {  // prefix
							uint64_t to_move = range.source_end - seed_range.start;
							next_seeds_queue.emplace(
								range.dest_start + seed_range.start - range.source_start,
								range.dest_start + seed_range.start + to_move - range.source_start
							);
							seeds_queue.emplace(
								seed_range.start + to_move,
								seed_range.end
							);
							found = true; break;
						}
					}
				} else {  // seed start before range start
					if (seed_range.end <= range.source_end) {  // seed end before range end
						if (seed_range.end > range.source_start) {  // suffix
							uint64_t to_not_move = range.source_start - seed_range.start;
							seeds_queue.emplace(
								seed_range.start,
								seed_range.start + to_not_move
							);
							next_seeds_queue.emplace(
								range.dest_start + seed_range.start + to_not_move - range.source_start,
								range.dest_start + seed_range.end - range.source_start
							);
							found = true; break;
						}
					} else {  // range inside seed
						uint64_t to_not_move = range.source_start - seed_range.start;
						seeds_queue.emplace(
							seed_range.start,
							seed_range.start + to_not_move
						);
						uint64_t to_move = range.source_end - range.source_start;
						next_seeds_queue.emplace(
							range.dest_start + seed_range.start + to_not_move - range.source_start,
							range.dest_start + seed_range.start + to_not_move + to_move - range.source_start
						);
						seeds_queue.emplace(
							seed_range.start + to_not_move + to_move,
							seed_range.end
						);
						found = true; break;
					}
				}
			}
			if (!found) {
				next_seeds_queue.push(seed_range);
			}
		}
		swap(seeds_queue, next_seeds_queue);
	}

	uint64_t res = UINT64_MAX;
	while (!seeds_queue.empty()) {
		seed_range_t seed_range = seeds_queue.front();
		seeds_queue.pop();
		res = min(res, seed_range.start);
	}

	cout << res << endl;
}

#include <bits/stdc++.h>
using namespace std;

#define MAX_H 100000

#define GET(line, bit) ((line >> (bit)) & 1)
#define SET(line, bit) (line |= 1 << (bit))

uint8_t grid[MAX_H];
string instrs;

struct shape_t {
	uint64_t h;
	int x;
	vector <pair <uint64_t, int>> blocks;

	shape_t(vector <pair <uint64_t, int>> blocks): h(0), x(2), blocks(blocks) {}
	shape_t(const shape_t& obj) = default;

	bool move(char dir) {
		int dx = dir == '<' ? -1 : 1;
		bool can_move_hor = true;
		for (auto [py, px] : blocks) {
			if (px + x + dx < 0 || px + x + dx > 6 || GET(grid[py + h], px + x + dx)) {
				can_move_hor = false;
				break;
			}
		}
		if (can_move_hor) {
			x += dx;
		}

		bool can_move_down = true;
		for (auto [py, px] : blocks) {
			if (py + h - 1 <= 0 || GET(grid[py + h - 1], px + x)) {
				can_move_down = false;
				break;
			}
		}

		if (!can_move_down) {
			for (auto [py, px] : blocks) {
				SET(grid[py + h], px + x);
			}
			return false;
		} else {
			h--;
			return true;
		}
	}

	uint64_t get_highest() {
		uint64_t res = 0;
		for (auto [py, ignore] : blocks) {
			res = max(res, py + h);
		}
		return res;
	}
};

shape_t shapes[5] = {
	shape_t({{0, 0}, {0, 1}, {0, 2}, {0, 3}}),
	shape_t({{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}}),
	shape_t({{0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2}}),
	shape_t({{0, 0}, {1, 0}, {2, 0}, {3, 0}}),
	shape_t({{0, 0}, {0, 1}, {1, 0}, {1, 1}})
};

uint64_t do_move(size_t shape_ind, size_t& move_ind, uint64_t highest) {
	shape_t shape = shapes[shape_ind];
	shape.h = highest + 4;

	while (shape.move(instrs[move_ind++ % instrs.size()]));
	return shape.get_highest();
}

#define MIN_H 1000
string get_state(uint64_t height) {
	string res = string(MIN_H, '\0');
	assert(height > MIN_H);
	for (uint64_t i = height - MIN_H + 1, j = 0; j <= MIN_H; i++, j++) {
		res[j] = (char)grid[i];
	}
	return res;
}

int main () {
	cin >> instrs;
	uint64_t highest = 0;

	unordered_map <string, pair <size_t, uint64_t>> states;  // state, index, height

	bool found_cycle = false;
	size_t todo = 1000000000000UL;
	size_t move_ind = 0;
	uint64_t skipped_height = -1;
	for (size_t block_ind = 0; block_ind < todo; block_ind++) {
		highest = max(highest, do_move(block_ind % 5, move_ind, highest));

		if (!found_cycle && highest > MIN_H) {
			string state = get_state(highest);
			if (states.find(state) != states.end()) {
				found_cycle = true;
				auto [prev_ind, prev_height] = states[state];
				size_t cycle_length = block_ind - prev_ind;
				uint64_t cycle_height = highest - prev_height;
				size_t skipped_cycles = (todo - block_ind) / cycle_length;
				size_t skipped_blocks = skipped_cycles * cycle_length;
				skipped_height = skipped_cycles * cycle_height;
				block_ind += skipped_blocks;
			} else {
				states[state] = make_pair(block_ind, highest);
			}
		}
	}
	assert(found_cycle);

	cout << (highest + skipped_height) << endl;
}

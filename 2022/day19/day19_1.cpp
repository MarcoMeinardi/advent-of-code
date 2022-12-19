#include <bits/stdc++.h>
using namespace std;

enum materials_t {
	ORE,
	CLAY,
	OBSIDIAN,
	GEODE
};

#define MAX_ORE 10
#define MAX_CLAY 40
#define MAX_OBSIDIAN 40
#define MAX_ORE_ROBOTS 10
#define MAX_CLAY_ROBOTS 10
#define MAX_OBSIDIAN_ROBOTS 10
const int max_time = 24;
const int max_resources[3] = {MAX_ORE, MAX_CLAY, MAX_OBSIDIAN};
const int max_robots[3] = {MAX_ORE_ROBOTS, MAX_CLAY_ROBOTS, MAX_OBSIDIAN_ROBOTS};

int costs[4][3];

struct state_t {
	uint8_t resources[4];
	uint8_t robots[3];
	uint8_t t;

	state_t() {
		memset(resources, 0, sizeof(resources));
		memset(robots + 1, 0, sizeof(robots) - sizeof(robots[0]));
		robots[ORE] = 1;
		t = 0;
	};
	state_t(const state_t& obj) = default;

	void produce() {
		for (size_t i = 0; i < 3; i++) {
			resources[i] = min(max_resources[i], resources[i] + robots[i]);
		}
	}

};

// time, ore, clay, obsidian, ore_robots, clay_robots, obsidian_robots => geode
uint8_t best[max_time + 1][MAX_ORE + 1][MAX_CLAY + 1][MAX_OBSIDIAN + 1][MAX_ORE_ROBOTS + 1][MAX_CLAY_ROBOTS + 1][MAX_OBSIDIAN_ROBOTS + 1];

bool check_set_best(state_t& state) {
	uint8_t* element = &best[state.t][state.resources[ORE]][state.resources[CLAY]][state.resources[OBSIDIAN]][state.robots[ORE]][state.robots[CLAY]][state.robots[OBSIDIAN]];
	if (*element != numeric_limits<uint8_t>::max() && *element >= state.resources[GEODE]) return false;
	*element = state.resources[GEODE];
	return true;
}
bool check_good(state_t& state) {
	uint8_t* element = &best[state.t][state.resources[ORE]][state.resources[CLAY]][state.resources[OBSIDIAN]][state.robots[ORE]][state.robots[CLAY]][state.robots[OBSIDIAN]];
	return *element == state.resources[GEODE];
}

int solve() {
	memset(best, numeric_limits<uint8_t>::max(), sizeof(best));

	state_t initial_state = state_t();
	queue <state_t> q;
	ignore = check_set_best(initial_state);
	q.push(initial_state);

	while (!q.empty()) {
		state_t actual_state = q.front();
		q.pop();
		if (actual_state.t == max_time) {
			continue;
		}
		if (!check_good(actual_state)) continue;

		actual_state.t++;
		for (int i = 0; i < 4; i++) {
			bool can_build = true;
			for (int j = 0;  j < 3; j++) {
				if (actual_state.resources[j] < costs[i][j]) {
					can_build = false;
					break;
				}
			}
			if (can_build) {
				state_t next_state = actual_state;
				next_state.produce();
				for (int j = 0; j < 3; j++) {
					next_state.resources[j] -= costs[i][j];
				}
				if (i == GEODE) {
					next_state.resources[GEODE] += max_time - actual_state.t;
				} else {
					if (actual_state.robots[i] < max_robots[i])
						next_state.robots[i]++;
					else {
						continue;
					}
				}
				if (check_set_best(next_state))
					q.push(next_state);
			}
		}
		actual_state.produce();
		if (check_set_best(actual_state))
			q.push(actual_state);
	}

	int result = 0;
	uint8_t* best_ptr = (uint8_t*)best;
	for (size_t i = 0; i < sizeof(best); i++, best_ptr++) {
		if (*best_ptr != numeric_limits<uint8_t>::max())
			result = max(result, (int)*best_ptr);
	}
	return result;
}

int main () {
	int total = 0;
	int id;

	while (scanf(
		"Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.%*c",
		&id, &costs[ORE][ORE], &costs[CLAY][ORE], &costs[OBSIDIAN][ORE],
		&costs[OBSIDIAN][CLAY], &costs[GEODE][ORE], &costs[GEODE][OBSIDIAN]) > 0
	) {
		int res = solve();
		total += res * id;
	}

	cout << total << endl;
}

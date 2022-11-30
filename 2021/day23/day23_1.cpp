#include <bits/stdc++.h>
using namespace std;

const int scores[5] = {-1, 1, 10, 100, 1000};

uint64_t compress(uint8_t rooms[4][2], uint8_t* hallway) {
	uint64_t res = 0;
	for (int i = 0; i < 11; i++) {
		res <<= 3;
		res |= hallway[i];
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			res <<= 3;
			res |= rooms[i][j];
		}
	}
	return res;
}

bool is_solved(uint8_t rooms[4][2]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			if (rooms[i][j] != i + 1) {
				return false;
			}
		}
	}
	return true;
}

int from_hallway(uint8_t rooms[4][2], uint8_t* hallway, int ind, int& move) {
	if (hallway[ind] == 0) return -1;

	int next_pos = hallway[ind] * 2;
	int depth = -1;
	int room = hallway[ind] - 1;
	int score;

	for (int i = 1; i >= 0; i--) {
		if (rooms[room][i] == 0) {
			depth = i;
			break;
		}
		if (rooms[room][i] != hallway[ind]) {
			return -1;
		}
	}

	if (next_pos > ind) {
		for (int i = ind + 1; i <= next_pos; i++) {
			if (hallway[i] != 0) {
				return -1;
			}
		}
	} else {
		for (int i = ind - 1; i >= next_pos; i--) {
			if (hallway[i] != 0) {
				return -1;
			}
		}
	}

	// move = 
	// 	4 bit, prev hallway position
	// 	2 bit, room
	// 	1 bit, room depth
	move = ind | ((hallway[ind] - 1) << 4) | (depth << 6);
	score = scores[hallway[ind]] * (abs(ind - next_pos) + depth + 1);
	rooms[room][depth] = hallway[ind];
	hallway[ind] = 0;
	return score;
}

void undo_from_hallway_move(uint8_t rooms[4][2], uint8_t* hallway, int move) {
	int prev_hallway_pos = move & 0b1111;
	int room = (move & 0b110000) >> 4;
	int depth = (move & 0b1000000) >> 6;

	hallway[prev_hallway_pos] = rooms[room][depth];
	rooms[room][depth] = 0;
}

int to_room(uint8_t rooms[4][2], uint8_t* hallway, int room, int depth, int& move) {
	if (rooms[room][depth] == 0 || rooms[room][depth] == room + 1) return -1;

	int actual_pos = room * 2 + 2;
	int next_room = rooms[room][depth] - 1;
	int next_depth = -1;
	int next_pos = rooms[room][depth] * 2;
	int score;

	for (int i = depth - 1; i >= 0; i--) {
		if (rooms[room][i] != 0) {
			return -1;
		}
	}

	for (int i = 1; i >= 0; i--) {
		if (rooms[next_room][i] == 0) {
			next_depth = i;
			break;
		}
		if (rooms[next_room][i] != rooms[room][depth]) {
			return -1;
		}
	}

	if (next_pos > actual_pos) {
		for (int i = actual_pos + 1; i <= next_pos; i++) {
			if (hallway[i] != 0) {
				return -1;
			}
		}
	} else {
		for (int i = actual_pos - 1; i >= next_pos; i--) {
			if (hallway[i] != 0) {
				return -1;
			}
		}
	}

	// move = 
	// 	2 bit, prev room
	// 	1 bit, prev depth
	// 	2 bit, room
	// 	1 bit, depth
	move = room | (depth << 2) | (next_room << 3) | (next_depth << 5);
	score = scores[rooms[room][depth]] * (depth + 1 + next_depth + 1 + abs(actual_pos - next_pos));
	rooms[next_room][next_depth] = rooms[room][depth];
	rooms[room][depth] = 0;
	return score;
}

void undo_to_room_move(uint8_t rooms[4][2], uint8_t* hallway, int move) {
	int prev_room = move & 0b11;
	int prev_depth = (move & 0b100) >> 2;
	int room = (move & 0b11000) >> 3;
	int depth = (move & 0b100000) >> 5;

	rooms[prev_room][prev_depth] = rooms[room][depth];
	rooms[room][depth] = 0;
}

int to_hallway(uint8_t rooms[4][2], uint8_t* hallway, int room, int depth, int ind, int& move) {
	if (rooms[room][depth] == 0 || hallway[ind] != 0) return -1;
	if (ind >= 2 && ind <= 8 && ind % 2 == 0) return -1;

	bool make_sense = false;
	int actual_pos = room * 2 + 2;
	int score;
	if (rooms[room][depth] != room + 1) make_sense = true;
	else {
		for (int i = depth + 1; i < 2; i++) {
			if (rooms[room][i] != rooms[room][depth]) {
				make_sense = true;
			}
		}
	}
	if (!make_sense) return -1;

	for (int i = depth - 1; i >= 0; i--) {
		if (rooms[room][i] != 0) {
			return -1;
		}
	}

	if (actual_pos > ind) {
		for (int i = actual_pos - 1; i >= ind; i--) {
			if (hallway[i] != 0) {
				return -1;
			}
		}
	} else {
		for (int i = actual_pos + 1; i <= ind; i++) {
			if (hallway[i] != 0) {
				return -1;
			}
		}
	}

	// move = 
	// 	4 bit, hallway position
	// 	2 bit, prev room
	// 	1 bit, prev room depth
	move = ind | (room << 4) | (depth << 6);
	score = scores[rooms[room][depth]] * (abs(actual_pos - ind) + depth + 1);
	hallway[ind] = rooms[room][depth];
	rooms[room][depth] = 0;
	return score;
}

void undo_to_hallway_move(uint8_t rooms[4][2], uint8_t* hallway, int move) {
	int hallway_pos = move & 0b1111;
	int prev_room = (move & 0b110000) >> 4;
	int prev_depth = (move & 0b1000000) >> 6;

	rooms[prev_room][prev_depth] = hallway[hallway_pos];
	hallway[hallway_pos] = 0;
}

map <uint64_t, int> cache;
int play(uint8_t rooms[4][2], uint8_t* hallway, int prev_score, int best_score) {
	int act_score;
	int move;
	uint64_t compressed;

	if (prev_score >= best_score) {
		return 1e9 + 5;
	}

	compressed = compress(rooms, hallway);
	auto it = cache.find(compressed);
	if (it != cache.end()) {
		if (prev_score >= it->second) {
			return 1e9 + 5;
		} else {
			it->second = prev_score;
		}
	} else {
		cache[compressed] = prev_score;
	}

	if (is_solved(rooms)) {
		return prev_score;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			act_score = to_room(rooms, hallway, i, j, move);
			if (act_score != -1) {
				act_score = play(rooms, hallway, prev_score + act_score, best_score);
				best_score = min(best_score, act_score);
				undo_to_room_move(rooms, hallway, move);
			}
		}
	}

	for (int i = 0; i < 11; i++) {
		act_score = from_hallway(rooms, hallway, i, move);
		if (act_score != -1) {
			act_score = play(rooms, hallway, prev_score + act_score, best_score);
			best_score = min(best_score, act_score);
			undo_from_hallway_move(rooms, hallway, move);
		}
	}	

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 11; k++) {
				act_score = to_hallway(rooms, hallway, i, j, k, move);
				if (act_score != -1) {
					act_score = play(rooms, hallway, prev_score + act_score, best_score);
					best_score = min(best_score, act_score);
					undo_to_hallway_move(rooms, hallway, move);
				}
			}
		}
	}

	return best_score;
}

int main () {
	uint8_t hallway[11] = {};
	uint8_t rooms[4][2];
	char line[20];

	scanf("%s\n%s\n%s", line, line, line);
	for (int i = 0; i < 4; i++)
		rooms[i][0] = line[(i + 1) * 2 + 1] - 'A' + 1;
	scanf("%s", line);
	for (int i = 0; i < 4; i++)
		rooms[i][1] = line[i * 2 + 1] - 'A' + 1;

	cout << play(rooms, hallway, 0, 1e9 + 5) << endl;
	return 0;
}
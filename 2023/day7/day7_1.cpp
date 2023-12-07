#include <bits/stdc++.h>
using namespace std;

#define HAND_SIZE 5

char values[0x80];

__attribute__((constructor)) void set_values()
{
	for (int i = '2'; i <= '9'; i++) {
		values[i] = i - '0';
	}
	values['T'] = 10;
	values['J'] = 11;
	values['Q'] = 12;
	values['K'] = 13;
	values['A'] = 14;
}

struct hand_t {
	uint64_t bid;
	char cards[8];
	int score;

	hand_t (string cards_str, uint64_t bid) : bid(bid)
	{
		for (int i = 0; i < HAND_SIZE; i++) {
			cards[i] = values[(size_t)cards_str[i]];
		}

		get_score();
	}

	void get_score()
	{
		int freq[16] = {0};
		for (int i = 0; i < HAND_SIZE; i++) {
			freq[(size_t)cards[i]]++;
		}

		bool has_three = false, has_two = false;
		for (int i = 2; i < 15; i++) {
			if (freq[i] == 5) {
				score = 6;
				return;
			} else if (freq[i] == 4) {
				score = 5;
				return;
			} else if (freq[i] == 3) {
				has_three = true;
			} else if (freq[i] == 2) {
				if (has_two) {
					score = 2;
					return;
				} else {
					has_two = true;
				}
			}
		}

		if (has_three && has_two) {
			score = 4;
		} else if (has_three) {
			score = 3;
		} else if (has_two) {
			score = 1;
		} else {
			score = 0;
		}
	}

	bool operator<(const hand_t &other) const
	{
		if (score != other.score) {
			return score < other.score;
		} else {
			return strcmp(cards, other.cards) < 0;
		}
	}
};

int main ()
{
	vector<hand_t> hands;
	string cards;
	uint64_t bid;

	while (cin >> cards >> bid) {
		hands.emplace_back(cards, bid);
	}

	sort(hands.begin(), hands.end());

	uint64_t tot = 0;
	for (size_t i = 0; i < hands.size(); i++) {
		tot += hands[i].bid * (i + 1);
	}

	cout << tot << endl;
}

#include <bits/stdc++.h>
using namespace std;

int main () {
	stack <char> st;
	string line;
	bool wrong;
	uint64_t score;
	vector <uint64_t> res;

	uint64_t scores[0x80] = {};
	scores['('] = 1;
	scores['['] = 2;
	scores['{'] = 3;
	scores['<'] = 4;
	char opposites[0x80];
	opposites[')'] = '(';
	opposites[']'] = '[';
	opposites['}'] = '{';
	opposites['>'] = '<';

	while (cin >> line) {
		wrong = false;
		for (char c : line) {
			if (scores[(int)c] == 0) {
				if (st.empty() || st.top() != opposites[(int)c]) {
					wrong = true;
					break;
				}
				st.pop();
			} else {
				st.push(c);
			}
		}
		if (wrong) {
			while (!st.empty()) st.pop();
			continue;
		}

		score = 0;
		while(!st.empty()) {
			score *= 5;
			score += scores[(int)st.top()];
			st.pop();
		}

		res.push_back(score);
	}

	sort(res.begin(), res.end());

	cout << res[res.size() / 2] << endl;
	return 0;
}
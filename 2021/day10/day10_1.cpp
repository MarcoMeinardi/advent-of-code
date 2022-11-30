#include <bits/stdc++.h>
using namespace std;

int main () {
	stack <char> st;
	string line;
	int tot = 0;

	int scores[0x80] = {};
	scores[')'] = 3;
	scores[']'] = 57;
	scores['}'] = 1197;
	scores['>'] = 25137;
	char opposites[256];
	opposites[')'] = '(';
	opposites[']'] = '[';
	opposites['}'] = '{';
	opposites['>'] = '<';
	

	while (cin >> line) {
		while(!st.empty()) st.pop();

		for (char c : line) {
			if (scores[(int)c] != 0) {
				if (st.empty() || st.top() != opposites[(int)c]) {
					tot += scores[(int)c];
					break;
				}
				st.pop();
			} else {
				st.push(c);
			}
		}
	}

	cout << tot << endl;
	return 0;
}
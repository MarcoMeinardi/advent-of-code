#include <bits/stdc++.h>
using namespace std;

int main () {
	string line;
	vector <string> lines;

	while (true) {
		getline(cin, line);
		if (line[1] == '1') break;
		lines.push_back(line);
	}
	int n = (lines[0].size() + 1) / 4;
	vector <stack <char>> stacks(n);

	for (int i = (int)lines.size() - 1; i >= 0; i--) {
		for (size_t j = 0, k = 1; k < lines[i].size(); j++, k += 4) {
			if (lines[i][k] != ' ') {
				stacks[j].push(lines[i][k]);
			}
		}
	}

	getline(cin, line);

	while (getline(cin, line)) {
		char* word = line.data();
		strtok(word, " ");  // move
		int q = atoi(strtok(NULL, " "));
		strtok(NULL, " ");  // from
		int from = atoi(strtok(NULL, " ")) - 1;
		strtok(NULL, " ");  // to
		int to = atoi(strtok(NULL, " ")) - 1;

		stack <char> foo_stack;
		while (q--) {
			foo_stack.push(stacks[from].top());
			stacks[from].pop();
		}
		while (!foo_stack.empty()) {
			stacks[to].push(foo_stack.top());
			foo_stack.pop();
		}
	}

	string res;
	for (stack <char>& s : stacks) {
		res += s.top();
	}
	cout << res << endl;
}

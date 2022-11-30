#include <bits/stdc++.h>
using namespace std;

#define BLOCK_SIZE 18
#define ADD 5
#define INC 15

struct block {
	int add;
	int inc;
};

int max_depth;
string solve(vector <block>& code, size_t ind, stack <int>& last) {
	if (ind == code.size()) {
		return "A";
	}
	string next;
	int to_match;

	if (code[ind].add < 0) {
		to_match = last.top() + code[ind].add;
		if (to_match < 1 || to_match > 9) {
			return "X";
		} else {
			last.pop();
			next = solve(code, ind + 1, last);
			if (next[0] != 'X') {
				return (char)(to_match + '0') + next;
			} else {
				last.push(to_match - code[ind].add);
				return "X";
			}
		}
	} else {
		for (int i = 9; i > 0; i--) {
			last.push(i + code[ind].inc);
			next = solve(code, ind + 1, last);
			if (next[0] != 'X') {
				return (char)(i + '0') + next;
			}
			last.pop();
		}
	}
	return "X";
}

int main () {
	vector <block> code;
	char line[30] = "";
	char operand[10];
	block act;
	stack <int> last;

	int cnt = 0;
	while(scanf("%[^\n]%*c", line) == 1) {
		if (cnt % BLOCK_SIZE == ADD) {
			sscanf(line, "%s %s %s", operand, operand, operand);
			act.add = atoi(operand);
		} else if (cnt % BLOCK_SIZE == INC) {
			sscanf(line, "%s %s %s", operand, operand, operand);
			act.inc = atoi(operand);
			code.push_back(act);
		}
		cnt++;
		memset(line, 0, sizeof(line));
		memset(operand, 0, sizeof(operand));
	}

	cout << solve(code, 0, last).substr(0, code.size()) << endl;
	return 0;
}
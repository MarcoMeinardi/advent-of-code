#include <bits/stdc++.h>
using namespace std;

unordered_map<string, size_t> str2ind;

size_t get_index(string s) {
	static size_t g_ind = 0;
	if (str2ind.find(s) != str2ind.end()) return str2ind[s];
	str2ind[s] = g_ind;
	return g_ind++;
}

#define MAX_MONKEYS 10000
#define ROOT 0

function<int64_t(size_t, size_t)> add = [] (size_t lhs, size_t rhs) { return lhs + rhs; };
function<int64_t(size_t, size_t)> sub = [] (size_t lhs, size_t rhs) { return lhs - rhs; };
function<int64_t(size_t, size_t)> mult = [] (size_t lhs, size_t rhs) { return lhs * rhs; };
function<int64_t(size_t, size_t)> idiv = [] (size_t lhs, size_t rhs) { return lhs / rhs; };
function<int64_t(size_t, size_t)> op[4]  = {add, sub, mult, idiv};

struct monkey_t {
	size_t m1;
	size_t m2;
	int64_t result;
	size_t operation;
	bool ready;

	monkey_t(int64_t n): result(n), ready(true) {}
	monkey_t(size_t m1_, size_t m2_, char op): m1(m1_), m2(m2_), ready(false) {
		if      (op == '+') operation = 0;
		else if (op == '-') operation = 1;
		else if (op == '*') operation = 2;
		else if (op == '/') operation = 3;
	}

	void evaluate(int64_t lhs, int64_t rhs) {
		result = op[operation](lhs, rhs);
	}
};

shared_ptr<monkey_t> monkeys[MAX_MONKEYS];

void parse_monkey(string& s) {
	string name = strtok(s.data(), ":");
	size_t index = get_index(name);
	string m1 = strtok(NULL, " ");
	if (isdigit(m1[0])) {
		monkeys[index] = make_shared<monkey_t>(stoll(m1));
		return;
	}
	string op = strtok(NULL, " ");
	string m2 = strtok(NULL, " ");
	monkeys[index] = make_shared<monkey_t>(get_index(m1), get_index(m2), op[0]);
}

int64_t dfs(size_t id) {
	shared_ptr<monkey_t> monkey = monkeys[id];
	if (monkey->ready) return monkey->result;

	int64_t lhs = dfs(monkey->m1);
	int64_t rhs = dfs(monkey->m2);
	monkey->evaluate(lhs, rhs);
	monkey->ready = true;
	return monkey->result;
}

int main () {
	ignore = get_index("root");

	string line;
	size_t n;
	while (getline(cin, line)) {
		parse_monkey(line);
		n++;
	}

	cout << dfs(ROOT) << endl;
}

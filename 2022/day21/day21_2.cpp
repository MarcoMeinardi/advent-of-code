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
#define ME 1

function<double(double, double)> add = [] (double lhs, double rhs)  { return lhs + rhs; };
function<double(double, double)> sub = [] (double lhs, double rhs)  { return lhs - rhs; };
function<double(double, double)> mult = [] (double lhs, double rhs) { return lhs * rhs; };
function<double(double, double)> idiv = [] (double lhs, double rhs) { return lhs / rhs; };
function<double(double, double)> op[4]  = {add, sub, mult, idiv};
function<double(double, double)> iop[4] = {sub, add, idiv, mult};

function<double(double, double)> inv_add = [] (double lhs, double rhs)  { return lhs - rhs; };
function<double(double, double)> inv_sub = [] (double lhs, double rhs)  { return -(lhs - rhs); };
function<double(double, double)> inv_mult = [] (double lhs, double rhs) { return lhs / rhs; };
function<double(double, double)> inv_idiv = [] (double lhs, double rhs) { return 1.0 / (lhs / rhs); };
function<double(double, double)> inv_iop[4] = {inv_add, inv_sub, inv_mult, inv_idiv};

struct monkey_t {
	size_t m1;
	size_t m2;
	double result;
	size_t operation;
	bool ready;

	monkey_t(double n): result(n), ready(true) {}
	monkey_t(size_t m1_, size_t m2_, char op): m1(m1_), m2(m2_), ready(false) {
		if      (op == '+') operation = 0;
		else if (op == '-') operation = 1;
		else if (op == '*') operation = 2;
		else if (op == '/') operation = 3;
	}

	void evaluate(double lhs, double rhs) {
		result = op[operation](lhs, rhs);
	}
	double ievaluate(double lhs, double rhs, bool inv) {
		if (inv) {
			return inv_iop[operation](lhs, rhs);
		} else {
			return iop[operation](lhs, rhs);
		}
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

bool affected_by_me[MAX_MONKEYS];
optional<double> calc_known_side(size_t id) {
	if (id == ME) return nullopt;
	shared_ptr<monkey_t> monkey = monkeys[id];
	if (monkey->ready) return optional<double>(monkey->result);

	optional<double> lhs = calc_known_side(monkey->m1);
	optional<double> rhs = calc_known_side(monkey->m2);
	if (!lhs.has_value() || !rhs.has_value()) {
		affected_by_me[id] = true;
		return nullopt;
	}

	monkey->evaluate(lhs.value(), rhs.value());
	monkey->ready = true;
	return optional<double>(monkey->result);
}

void get_my_value(size_t id, double to_match) {
	shared_ptr monkey = monkeys[id];
	if (id == ME) {
		monkey->result = to_match;
		return;
	}
	if (affected_by_me[monkey->m1]) {
		to_match = monkey->ievaluate(to_match, monkeys[monkey->m2]->result, false);
		get_my_value(monkey->m1, to_match);
	} else {
		to_match = monkey->ievaluate(to_match, monkeys[monkey->m1]->result, true);
		get_my_value(monkey->m2, to_match);
	}
}

int main () {
	ignore = get_index("root");  // 0 = ROOT
	ignore = get_index("humn");  // 1 = ME

	string line;
	size_t n;
	while (getline(cin, line)) {
		parse_monkey(line);
		n++;
	}

	double to_match;
	optional<double> lhs = calc_known_side(monkeys[ROOT]->m1);
	optional<double> rhs = calc_known_side(monkeys[ROOT]->m2);
	affected_by_me[ME] = true;
	if (lhs.has_value()) {
		to_match = lhs.value();
		get_my_value(monkeys[ROOT]->m2, to_match);
	} else {
		assert(rhs.has_value());
		to_match = rhs.value();
		get_my_value(monkeys[ROOT]->m1, to_match);
	}

	cout << (int64_t)monkeys[ME]->result << endl;
}

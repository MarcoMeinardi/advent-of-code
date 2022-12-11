#include <bits/stdc++.h>
using namespace std;

#define __lcm(a, b) ((a * b) / __gcd(a, b))

struct monkey_t {
	deque <uint64_t> items;
	function <uint64_t(uint64_t)> operation;
	uint64_t test_div;
	array <int, 2> throw_to;
	uint64_t inspected_items;
};

int main () {
	string word, line;
	vector <monkey_t> monkeys;

	do {
		getline(cin, line);  // Monkey x:
		cin >> word >> word;  // Starting items:
		monkeys.emplace_back();
		while (true) {
			cin >> word;
			monkeys.back().items.push_back(stoi(word));
			if (word.back() != ',') {
				break;
			}
		}

		cin >> word >> word >> word >> word;  // Operation: new = old
		string operation, operand;
		cin >> operation >> operand;
		if (operand == "old") {
			if (operation == "+")      monkeys.back().operation = [] (uint64_t old) { return old + old; };
			else if (operation == "*") monkeys.back().operation = [] (uint64_t old) { return old * old; };
			else assert(false);
		} else {
			uint64_t op = stoull(operand);
			if (operation == "+")      monkeys.back().operation = [op] (uint64_t old) { return old + op; };
			else if (operation == "*") monkeys.back().operation = [op] (uint64_t old) { return old * op; };
			else assert(false);
		}

		getline(cin, line);  // consume previous newline
		getline(cin, line);
		monkeys.back().test_div = stoi(line.substr(line.find_last_of(' ')));

		getline(cin, line);
		monkeys.back().throw_to[1] = stoi(line.substr(line.find_last_of(' ')));
		getline(cin, line);
		monkeys.back().throw_to[0] = stoi(line.substr(line.find_last_of(' ')));
	} while (getline(cin, line));  // empty line

	uint64_t big_module = 1;
	for (monkey_t& monkey : monkeys) {
		big_module = __lcm(big_module, monkey.test_div);
	}

	for (int i = 0; i < 10000; i++) {
		for (monkey_t& monkey : monkeys) {
			while (!monkey.items.empty()) {
				monkey.inspected_items++;
				int item = monkey.items.front();
				monkey.items.pop_front();
				item = monkey.operation(item) % big_module;
				monkeys[monkey.throw_to[item % monkey.test_div == 0]].items.push_back(item);
			}
		}
	}

	partial_sort(monkeys.begin(), monkeys.begin() + 2, monkeys.end(),
		[] (const monkey_t& m1, const monkey_t& m2) { return m1.inspected_items > m2.inspected_items; });

	cout << (monkeys[0].inspected_items * monkeys[1].inspected_items) << endl;
}

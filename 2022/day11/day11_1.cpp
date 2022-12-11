#include <bits/stdc++.h>
using namespace std;

struct monkey_t {
	deque <int> items;
	function <int(int)> operation;
	int test_div;
	array <int, 2> throw_to;
	int inspected_items;
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
			if (operation == "+")      monkeys.back().operation = [] (int old) { return old + old; };
			else if (operation == "*") monkeys.back().operation = [] (int old) { return old * old; };
			else assert(false);
		} else {
			int op = stoi(operand);
			if (operation == "+")      monkeys.back().operation = [op] (int old) { return old + op; };
			else if (operation == "*") monkeys.back().operation = [op] (int old) { return old * op; };
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

	for (int i = 0; i < 20; i++) {
		for (monkey_t& monkey : monkeys) {
			while (!monkey.items.empty()) {
				monkey.inspected_items++;
				int item = monkey.items.front();
				monkey.items.pop_front();
				item = monkey.operation(item);
				item /= 3;
				monkeys[monkey.throw_to[item % monkey.test_div == 0]].items.push_back(item);
			}
		}
	}

	partial_sort(monkeys.begin(), monkeys.begin() + 2, monkeys.end(),
		[] (const monkey_t& m1, const monkey_t& m2) { return m1.inspected_items > m2.inspected_items; });

	cout << (monkeys[0].inspected_items * monkeys[1].inspected_items) << endl;
}

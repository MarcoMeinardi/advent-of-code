#include <bits/stdc++.h>
using namespace std;

int var2int[0x80];
__attribute__((constructor)) void init_var2int()
{
	var2int['x'] = 0;
	var2int['m'] = 1;
	var2int['a'] = 2;
	var2int['s'] = 3;
}

struct rating_t {
	int val[4];

	rating_t() = default;
	rating_t(string s)
	{
		s = s.substr(1, s.size() - 2);
		char* token = strtok(s.data(), ",");
		parse_val(token);
		while ((token = strtok(NULL, ",")) != NULL) {
			parse_val(token);
		}
	}

	void parse_val(char* token)
	{
		int var = var2int[(int)token[0]];
		int value = stoi(token + 2);
		val[var] = value;
	}

	uint64_t tot_value() {
		return (uint64_t)val[0] + val[1] + val[2] + val[3];
	}
};

struct workflow_t {
	string label;
	int var;
	char op;
	int cmp;
	bool is_A;
	bool is_R;
	bool is_end;
	string to_goto;
	workflow_t* lft;
	workflow_t* rgt;

	workflow_t() = default;
	workflow_t(string s)
	{
		size_t column = s.find_first_of(':');
		if (column == string::npos) {
			is_end = true;
			string target = s.substr(0, column);
			if (target == "A") {
				is_A = true;
				is_R = false;
			} else if (target == "R") {
				is_A = false;
				is_R = true;
			} else {
				is_A = false;
				is_R = false;
				to_goto = target;
			}
			return;
		}
		is_end = false;
		size_t comma = s.find_first_of(',');

		string condition = s.substr(0, column);
		parse_condition(condition);

		lft = new workflow_t(s.substr(column + 1, comma - column - 1));
		rgt = new workflow_t(s.substr(comma + 1));
	}

	void parse_condition(string condition)
	{
		var = var2int[(int)condition[0]];
		op = condition[1];
		assert(op == '<' || op == '>');
		cmp = stoi(condition.substr(2));
	}

	bool apply(rating_t& rating);
};

unordered_map<string, workflow_t> workflows;

bool workflow_t::apply(rating_t& rating)
{
	if (is_end) {
		if (is_A) {
			return true;
		} else if (is_R) {
			return false;
		} else {
			return workflows[to_goto].apply(rating);
		}
	}

	bool correct;
	if (op == '<') {
		correct = rating.val[var] < cmp;
	} else {
		correct = rating.val[var] > cmp;
	}
	if (correct)
		return lft->apply(rating);
	else
		return rgt->apply(rating);
}

int main ()
{
	string line;
	while (getline(cin, line), !line.empty()) {
		size_t par = line.find_first_of('{');
		string label = line.substr(0, par);
		string workflow = line.substr(par + 1, line.size() - par - 2);
		workflows[label] = workflow_t(workflow);
	}

	vector<rating_t> ratings;
	while (getline(cin, line)) {
		ratings.emplace_back(line);
	}

	uint64_t tot = 0;
	for (rating_t& rating : ratings) {
		bool ok = workflows["in"].apply(rating);
		if (ok) tot += rating.tot_value();
	}

	cout << tot << endl;
}

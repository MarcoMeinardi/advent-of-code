#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> str2int;

int str2node(string& s)
{
	if (str2int.find(s) == str2int.end()) {
		int sz = (int)str2int.size();
		str2int[s] = sz;
	}
	return str2int[s];
}

int main ()
{
	string moves;
	cin >> moves;

	vector<array<string, 3>> input;
	vector<pair<int, int>> graph;

	vector<int> starts;
	set<int> ends;

	string start, left, right;
	string foo;

	while (cin >> start >> foo >> left >> right) {
		left = left.substr(1, left.size() - 2);
		right = right.substr(0, right.size() - 1);
		input.push_back({start, left, right});
		int start_int = str2node(start);
		if (start.back() == 'Z') {
			ends.insert(start_int);
		} else if (start.back() == 'A') {
			starts.push_back(start_int);
		}
	}

	graph.resize(input.size());
	for (size_t i = 0; i < input.size(); i++) {
		graph[i].first = str2node(input[i][1]);
		graph[i].second = str2node(input[i][2]);
	}

	// Every start reaches only a single end

	vector<uint64_t> steps;
	steps.reserve(starts.size());

	for (int node : starts) {
		uint64_t move_ind = 0;
		while (ends.find(node) == ends.end()) {
			if (moves[move_ind++ % moves.size()] == 'L') {
				node = graph[node].first;
			} else {
				node = graph[node].second;
			}
		}
		steps.push_back(move_ind);
	}

	uint64_t tot = steps[0];
	for (size_t i = 1; i < steps.size(); i++) {
		tot = lcm(tot, steps[i]);
	}
	cout << tot << endl;
}

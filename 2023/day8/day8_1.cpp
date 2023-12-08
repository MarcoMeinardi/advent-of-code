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
	int start_node = -1, end_node = -1;

	string start, left, right;
	string foo;

	while (cin >> start >> foo >> left >> right) {
		left = left.substr(1, left.size() - 2);
		right = right.substr(0, right.size() - 1);
		input.push_back({start, left, right});
		int start_int = str2node(start);
		if (start == "ZZZ") {
			end_node = start_int;
		} else if (start == "AAA") {
			start_node = start_int;
		}
	}
	assert(start_node != -1 && end_node != -1);

	graph.resize(input.size());
	for (size_t i = 0; i < input.size(); i++) {
		graph[i].first = str2node(input[i][1]);
		graph[i].second = str2node(input[i][2]);
	}

	int tot = 0;
	int node = start_node;
	while (node != end_node) {
		if (moves[tot++ % moves.size()] == 'L') {
			node = graph[node].first;
		} else {
			node = graph[node].second;
		}
	}

	cout << tot << endl;
}

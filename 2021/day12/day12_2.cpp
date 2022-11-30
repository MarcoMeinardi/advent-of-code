#include <bits/stdc++.h>
using namespace std;

#define START 0
#define END 1

int explore(int node, vector <vector <int>>& graph, vector <bool>& small, vector <bool>& vis, bool has_double_visited) {
	if (node == END) {
		return 1;
	}
	if (node == START) {
		return 0;
	}

	bool just_double = false;
	if (vis[node]) {
		if (has_double_visited) {
			return 0;
		}
		has_double_visited = true;
		just_double = true;
	}

	int tot = 0;
	vis[node] = small[node];
	for (int neightbour : graph[node]) {
		tot += explore(neightbour, graph, small, vis, has_double_visited);
	}
	vis[node] = just_double;
	return tot;
}

int main () {
	vector <vector <int>> graph (2);
	vector <bool> small (2);
	unordered_map <string, int> conv;
	string line;
	string a, b;
	int ia, ib;
	int i;
	int n_nodes = 2;
	vector <bool> vis;
	int tot = 0;
	conv["start"] = START;
	conv["end"] = END;

	while(cin >> line) {
		a.clear();
		b.clear();
		for (i = 0; line[i] != '-'; i++) {
			a += line[i];
		}
		i++;
		for (; line[i]; i++) {
			b += line[i];
		}

		if (conv.find(a) == conv.end()) {
			conv[a] = n_nodes;
			graph.push_back({});
			small.push_back('a' <= a[0] && a[0] <= 'z');
			n_nodes++;
		}
		if (conv.find(b) == conv.end()) {
			conv[b] = n_nodes;
			graph.push_back({});
			small.push_back('a' <= b[0] && b[0] <= 'z');
			n_nodes++;
		}
		ia = conv[a], ib = conv[b];

		graph[ia].push_back(ib);
		graph[ib].push_back(ia);
	}

	vis = vector <bool> (n_nodes, false);
	for (int neightbour : graph[START]) {
		tot += explore(neightbour, graph, small, vis, false);
	}

	cout << tot << endl;
	return 0;
}
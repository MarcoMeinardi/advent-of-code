#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100

unordered_map <string, size_t> str2ind;

int n;
int costs[MAX_N][MAX_N];
int flows[MAX_N];

int get_ind(string s) {
	static int g_ind = 0;
	if (str2ind.find(s) != str2ind.end()) return str2ind[s];
	str2ind[s] = g_ind;
	return g_ind++;
}

void parse_line(string& line) {
	char* data = line.data();
	ignore = strtok(data, " ");
	int ind = get_ind(strtok(NULL, " "));

	ignore = strtok(NULL, "=");
	flows[ind] = atoi(strtok(NULL, ";"));

	for (int i = 0; i < 4; i++)
		ignore = strtok(NULL, " ");

	char* child_name;
	while ((child_name = strtok(NULL, ","))) {
		child_name = *child_name == ' ' ? child_name + 1 : child_name;
		costs[ind][get_ind(child_name)] = 1;
	}
}

bool transitivity() {
	bool change = false;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || costs[i][j] == -1) continue;
			for (int k = 0; k < n; k++) {
				if (k == i || k == j || costs[j][k] == -1) continue;
				if (costs[i][k] == -1 || costs[i][j] + costs[j][k] < costs[i][k]) {
					change = true;
					costs[i][k] = costs[i][j] + costs[j][k];
				}
			}
		}
	}

	return change;
}

bool vis[MAX_N];
int dfs(int me, int ele, int my_depth = 0, int ele_depth = 0) {
	if ((me != 0 && vis[me]) || (ele != 0 && vis[ele])) return 0;
	if (ele_depth >= my_depth) {
		if (my_depth >= 26) return 0;
		vis[me] = true;
		int node_flow = flows[me] * (26 - my_depth - 1);
		if (flows[me]) my_depth++;

		int res = 0;
		for (int i = 0; i < n; i++) {
			if (flows[i] == 0) continue;
			res = max(res, dfs(i, ele, my_depth + costs[me][i], ele_depth));
		}

		vis[me] = false;
		return res + node_flow;

	} else {
		if (ele_depth >= 26) return 0;
		vis[ele] = true;
		int node_flow = flows[ele] * (26 - ele_depth - 1);
		if (flows[ele]) ele_depth++;

		int res = 0;
		for (int i = 0; i < n; i++) {
			if (flows[i] == 0) continue;
			res = max(res, dfs(me, i, my_depth, ele_depth + costs[ele][i]));
		}

		vis[ele] = false;
		return res + node_flow;
	}
}

int main () {
	string line;
	ignore = get_ind("AA");
	n = 0;

	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			costs[i][j] = i == j ? 0 : -1;
		}
	}

	while (getline(cin, line)) {
		n++;
		parse_line(line);
	}

	while (transitivity());

	cout << dfs(0, 0) << endl;	
}

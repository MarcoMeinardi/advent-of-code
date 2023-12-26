#include <bits/stdc++.h>
using namespace std;

unordered_map<string, size_t> name2id;
size_t n = 0;
size_t get_id(string& s)
{
	if (name2id.find(s) == name2id.end()) {
		name2id[s] = n++;
	}
	return name2id[s];
}

bool bfs(vector<vector<size_t>>& residual_graph, vector<size_t>& parent, size_t source, size_t sink)
{
	size_t V = residual_graph.size();
	vector<bool> visited(V, false);

	queue<size_t> q;
	q.push(source);
	visited[source] = true;
	parent[source] = -1;

	while (!q.empty()) {
		size_t u = q.front();
		q.pop();

		for (size_t v = 0; v < V; v++) {
			if (!visited[v] && residual_graph[u][v] > 0) {
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return visited[sink];
}

void dfs(vector<vector<size_t>>& residual_graph, vector<bool>& visited, size_t u)
{
	visited[u] = true;
	size_t V = residual_graph.size();

	for (size_t v = 0; v < V; v++) {
		if (!visited[v] && residual_graph[u][v] > 0) {
			dfs(residual_graph, visited, v);
		}
	}
}

set<pair<size_t, size_t>> min_cut(vector<vector<size_t>>& graph, size_t source, size_t sink)
{
	size_t V = graph.size();
	vector<vector<size_t>> residual_graph(V, vector<size_t>(V, 0));
	vector<size_t> parent(V, 0);

	for (size_t u = 0; u < V; u++) {
		for (size_t v : graph[u]) {
			residual_graph[u][v] = 1;
		}
	}

	size_t max_flow = 0;

	while (bfs(residual_graph, parent, source, sink)) {
		size_t path_flow = INT_MAX;
		for (size_t v = sink; v != source; v = parent[v]) {
			size_t u = parent[v];
			path_flow = min(path_flow, residual_graph[u][v]);
		}

		for (size_t v = sink; v != source; v = parent[v]) {
			size_t u = parent[v];
			residual_graph[u][v] -= path_flow;
			residual_graph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	vector<bool> visited(V, false);
	dfs(residual_graph, visited, source);

	set<pair<size_t, size_t>> cut_edges;
	for (size_t u = 0; u < V; u++) {
		for (size_t v = 0; v < V; v++) {
			if (visited[u] && !visited[v] && find(graph[u].begin(), graph[u].end(), v) != graph[u].end()) {
				cut_edges.emplace(u, v);
			}
		}
	}

	return cut_edges;
}

size_t count_connected(vector<vector<size_t>>& graph, size_t node, vector<bool>& vis, set<pair<size_t, size_t>>& cut)
{
	if (vis[node]) return 0;
	vis[node] = true;

	size_t res = 1;
	for (size_t next : graph[node]) {
		if (cut.find({node, next}) == cut.end()) {
			res += count_connected(graph, next, vis, cut);
		}
	}

	return res;
}

int main()
{
	vector<vector<size_t>> graph;
	string line;

	while (getline(cin, line)) {
		stringstream ss(line);
		string from, to;
		ss >> from;
		from.pop_back();
		size_t from_id = get_id(from);
		if (graph.size() <= from_id) {
			graph.resize(from_id + 1);
		}

		while (ss >> to) {
			size_t to_id = get_id(to);
			if (graph.size() <= to_id) {
				graph.resize(to_id + 1);
			}
			graph[from_id].push_back(to_id);
			graph[to_id].push_back(from_id);
		}
	}

	set<pair<size_t, size_t>> cut_edges;
	for (size_t i = 0; i < n; i++) {
		cut_edges = min_cut(graph, i, (i + 1) % n);
		if (cut_edges.size() == 3) {
			break;
		}
	}
	assert(cut_edges.size() == 3);

	vector<bool> visited(n, false);
	vector<size_t> groups_size;
	for (size_t i = 0; i < n; i++) {
		if (visited[i]) continue;
		groups_size.push_back(count_connected(graph, i, visited, cut_edges));
	}
	assert(groups_size.size() == 2);

	cout << groups_size[0] * groups_size[1] << endl;

	return 0;
}

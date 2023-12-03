#include <bits/stdc++.h>
using namespace std;

const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int n, m;

bool is_next_symbol(vector<string>& mat, int y, int x)
{
	for (int i = 0; i < 8; i++) {
		int ny = y + dy[i], nx = x + dx[i];
		if (ny < n && ny >= 0 && nx < m && nx >= 0 && !isdigit(mat[ny][nx]) && mat[ny][nx] != '.') {
			return true;
		}
	}
	return false;
}

bool check_valid(vector<string>& mat, int y, int x)
{
	while (x < m && isdigit(mat[y][x])) {
		if (is_next_symbol(mat, y, x)) {
			return true;
		}
		x++;
	}
	return false;
}

int main ()
{
	vector<string> mat;
	string line;
	while (cin >> line) {
		mat.push_back(line);
	}
	n = mat.size();
	m = mat[0].size();

	int tot = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (isdigit(mat[y][x]) && check_valid(mat, y, x)) {
				tot += stoi(&mat[y][x]);
				while (x < m && isdigit(mat[y][x])) {
					x++;
				}
			}
		}
	}
	cout << tot << endl;
}

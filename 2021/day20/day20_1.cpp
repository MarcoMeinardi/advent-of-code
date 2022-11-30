#include <bits/stdc++.h>
using namespace std;

#define CYCLES 2
#define BORDER 2

const int dy[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dx[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

int main () {
	string algo;
	string line;
	vector <string> lines;
	int n, m;
	int num;
	int ny, nx;
	int tot = 0;
	vector <vector <char>> image, new_image;

	cin >> algo;

	while(cin >> line) {
		lines.push_back(line);
	}
	n = lines.size() + (CYCLES + BORDER) * 2;
	m = lines[0].size() + (CYCLES + BORDER) * 2;

	image.resize(n, vector <char> (m, '.'));
	new_image.resize(n, vector <char> (m));
	

	for (int i = 0; i < n - (CYCLES + BORDER) * 2; i++) {
		for (int j = 0; j < m - (CYCLES + BORDER) * 2; j++) {
			image[i + CYCLES + BORDER][j + CYCLES + BORDER] = lines[i][j];
		}
	}

	for (int it = 0; it < CYCLES; it++) {
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++) {
				num = 0;
				for (int i = 0; i < 9; i++) {
					num <<= 1;
					ny = y + dy[i], nx = x + dx[i];
					if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
						if (algo[0] == '#') {
							if (algo[511] == '.') {
								num |= it & 1;
							} else {
								assert(false); // What? infinite ON pixels?
							}
						}
					} else {
						num |= image[y + dy[i]][x + dx[i]] == '#';
					}
				}
				new_image[y][x] = algo[num];
			}
		}
		swap(image, new_image);
	}

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			tot += image[y][x] == '#';
		}
	}

	cout << tot << endl;
	return 0;
}
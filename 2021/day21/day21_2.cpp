#include <bits/stdc++.h>
using namespace std;

uint64_t dp[10][10][31][31][2][2];

uint64_t* dfs(int* p, int* s, uint8_t turn) {
	uint64_t* res = dp[p[0]][p[1]][s[0]][s[1]][turn];
	uint64_t* next_res;
	if (res[0] != 0 || res[1] != 0) return res;

	if (s[turn ^ 1] >= 21) {
		res[turn ^ 1] = 1;
		return res;
	}

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			for (int k = 1; k <= 3; k++) {
				p[turn] += i + j + k, p[turn] %= 10;
				s[turn] += p[turn] + 1;

				next_res = dfs(p, s, turn ^ 1);

				s[turn] -= p[turn] + 1;
				p[turn] += 10 - (i + j + k), p[turn] %= 10;

				res[0] += next_res[0];
				res[1] += next_res[1];
			}
		}
	}

	return res;
}

int main () {
	int p[2] = {2, 7};
	int s[2] = {0, 0};
	p[0]--, p[1]--;
	uint64_t* res = dfs(p, s, 0);

	cout << max(res[0], res[1]) << endl;
	return 0;
}
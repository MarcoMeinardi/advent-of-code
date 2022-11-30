#include <bits/stdc++.h>
using namespace std;

#define MAX_DEPTH 40
#define COMPUTED 26

// for every pair
// for every layer
// save the number of letters created + if already computed
uint64_t saves[26][26][MAX_DEPTH + 1][27];
char subs[26][26];

void dfs(char a, char b, int depth) {
	if (saves[(int)a - 'A'][(int)b - 'A'][depth][COMPUTED] != 0) {
		return;
	}

	char sub = subs[(int)a - 'A'][(int)b - 'A'];

	// I though such a case existed...
	if (!sub) {
		dfs(a, b, depth + 1);
		saves[(int)a - 'A'][(int)b - 'A'][depth][COMPUTED] = 1;
	} else {
		dfs(a, sub, depth + 1);
		dfs(sub, b, depth + 1);
		saves[(int)a - 'A'][(int)b - 'A'][depth][(int)sub - 'A']++;
		for (int i = 0; i < 26; i++) {
			saves[(int)a - 'A'][(int)b - 'A'][depth][i] += saves[(int)a - 'A'][(int)sub - 'A'][depth + 1][i];
			saves[(int)a - 'A'][(int)b - 'A'][depth][i] += saves[(int)sub - 'A'][(int)b - 'A'][depth + 1][i];
		}
		saves[(int)a - 'A'][(int)b - 'A'][depth][COMPUTED] = 1;
	}
}

int main () {
	memset(saves, 0, 26 * 26 * (MAX_DEPTH + 1) * 27 * sizeof(uint64_t));
	memset(subs, 0, 26 * 26 * sizeof(char));
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			saves[i][j][MAX_DEPTH][COMPUTED] = 1;
		}
	}

	string a;
	char x, y, z;
	uint64_t freqs[0x80] = {};
	uint64_t nax = 0, nim = 1e18 + 5;

	cin >> a;
	scanf("%*c%*c");

	while(scanf("%c%c -> %c%*c", &x, &y, &z) == 3) {
		subs[(int)x - 'A'][(int)y - 'A'] = z;
	}

	for (int i = 0; a[i + 1]; i++) {
		freqs[(int)a[i] - 'A']++;
		dfs(a[i], a[i + 1], 0);
		for (int j = 0; j < 26; j++) {
			freqs[j] += saves[(int)a[i] - 'A'][(int)a[i + 1] - 'A'][0][j];
		}
	}
	freqs[(int)a[a.size() - 1] - 'A']++;

	for (int i = 0; i < 26; i++) {
		if (freqs[i]) {
			nax = max(nax, freqs[i]);
			nim = min(nim, freqs[i]);
		}
	}

	cout << (nax - nim) << endl;
	return 0;
}
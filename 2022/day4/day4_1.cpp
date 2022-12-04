#include <bits/stdc++.h>
using namespace std;

int main () {
	string sa, sb, sc, sd;

	int tot = 0;
	while (
		getline(cin, sa, '-') &&
		getline(cin, sb, ',') &&
		getline(cin, sc, '-') &&
		getline(cin, sd)
	) {
		int a, b, c, d;
		a = stoi(sa);
		b = stoi(sb);
		c = stoi(sc);
		d = stoi(sd);

		if ((a <= c && b >= d) || (c <= a && d >= b)) {
			tot++;
		}
	}

	cout << tot << endl;
}

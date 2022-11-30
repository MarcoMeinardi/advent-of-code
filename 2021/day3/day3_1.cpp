#include <bits/stdc++.h>
using namespace std;

int main () {
	string digits;
	int tot = 1;
	int freq[32] = {};
	unsigned int gamma = 0, epsilon;
	int len;

	cin >> digits;
	len = digits.size();
	do {
		tot++;
		for (int i = 0; i < len; i++) {
			freq[len - i - 1] += digits[i] == '1';
		}
	} while (cin >> digits);

	for (int i = len - 1; i >= 0; i--) {
		gamma <<= 1;
		gamma += freq[i] > tot / 2;
	}
	epsilon = ~gamma & ((1 << len) - 1);
	cout << (gamma * epsilon) << endl;

	return 0;
}
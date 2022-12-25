#include <bits/stdc++.h>
using namespace std;

int64_t SNAFUdigit2int[0x80];
int64_t SNAFU2int(string line) {
	int64_t res = 0;
	for (char c : line) {
		res *= 5;
		res += SNAFUdigit2int[(size_t)c];
	}

	return res;
}

char int2SNAFUdigit[5];
string int2SNAFU(int64_t n) {
	if (n == 0) return "0";
	vector<int> digits;
	while (n > 0) {
		digits.push_back(n % 5);
		n /= 5;
	}

	for (int i = 0; i < (int)digits.size(); i++) {
		if (digits[i] > 2) {
			if ((int)digits.size() == i - 1) digits.push_back(0);
			digits[i + 1] += 1;
			digits[i] -= 5;
		}
	}
	string res = "";
	reverse(digits.begin(), digits.end());
	for (int i : digits) {
		res += int2SNAFUdigit[i + 2];
	}

	return res;
}

int main () {
	SNAFUdigit2int[(int64_t)(int2SNAFUdigit[0] = '=')] = -2;
	SNAFUdigit2int[(int64_t)(int2SNAFUdigit[1] = '-')] = -1;
	SNAFUdigit2int[(int64_t)(int2SNAFUdigit[2] = '0')] = 0;
	SNAFUdigit2int[(int64_t)(int2SNAFUdigit[3] = '1')] = 1;
	SNAFUdigit2int[(int64_t)(int2SNAFUdigit[4] = '2')] = 2;
	string line;
	int64_t tot = 0;

	while (cin >> line) {
		tot += SNAFU2int(line);
	}

	cout << int2SNAFU(tot) << endl;
}

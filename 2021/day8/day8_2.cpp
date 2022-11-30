#include <bits/stdc++.h>
using namespace std;

int get_number(char* digits, int len, int* perm) {
	bool ok;
	switch(len) {
	case 2:
		for (int i = 0; i < 2; i++) {
			// 1
			if (
				digits[i] != perm[2] &&
				digits[i] != perm[5]
			) {
				return -1;
			}
		}
		return 1;
		break;
	case 3:
		for (int i = 0; i < 3; i++) {
			// 7
			if (
				digits[i] != perm[0] &&
				digits[i] != perm[2] &&
				digits[i] != perm[5]
			) {
				return -1;
			}
		}
		return 7;
		break;
	case 4:
		for (int i = 0; i < 4; i++) {
			// 4
			if (
				digits[i] != perm[1] &&
				digits[i] != perm[2] &&
				digits[i] != perm[3] &&
				digits[i] != perm[5]
			) {
				return -1;
			}
		}
		return 4;
		break;
	case 5:
		// 2
		ok = true;
		for (int i = 0; i < 5; i++) {
			if (
				digits[i] != perm[0] &&
				digits[i] != perm[2] &&
				digits[i] != perm[3] &&
				digits[i] != perm[4] &&
				digits[i] != perm[6]
			) {
				ok = false;
				break;
			}
		}
		if (ok) return 2;
		// 3
		ok = true;
		for (int i = 0; i < 5; i++) {
			if (
				digits[i] != perm[0] &&
				digits[i] != perm[2] &&
				digits[i] != perm[3] &&
				digits[i] != perm[5] &&
				digits[i] != perm[6]
			) {
				ok = false;
			break;
			}
		}
		if (ok) return 3;
		// 5
		ok = true;
		for (int i = 0; i < 5; i++) {
			if (
				digits[i] != perm[0] &&
				digits[i] != perm[1] &&
				digits[i] != perm[3] &&
				digits[i] != perm[5] &&
				digits[i] != perm[6]
			) {
				return -1;
			}
		}
		return 5;
	case 6:
		// 0
		ok = true;
		for (int i = 0; i < 6; i++) {
			if (
				digits[i] != perm[0] &&
				digits[i] != perm[1] &&
				digits[i] != perm[2] &&
				digits[i] != perm[4] &&
				digits[i] != perm[5] &&
				digits[i] != perm[6]
			) {
				ok = false;
				break;
			}
		}
		if (ok) return 0;
		// 6
		ok = true;
		for (int i = 0; i < 6; i++) {
			if (
				digits[i] != perm[0] &&
				digits[i] != perm[1] &&
				digits[i] != perm[3] &&
				digits[i] != perm[4] &&
				digits[i] != perm[5] &&
				digits[i] != perm[6]
			) {
				ok = false;
				break;
			}
		}
		if (ok) return 6;
		// 9
		ok = true;
		for (int i = 0; i < 6; i++) {
			if (
				digits[i] != perm[0] &&
				digits[i] != perm[1] &&
				digits[i] != perm[2] &&
				digits[i] != perm[3] &&
				digits[i] != perm[5] &&
				digits[i] != perm[6]
			) {
				return -1;
			}
		}
		return 9;
	case 7:
		return 8;
	default:
		assert(false);
	}
}

int main () {
	string line;
	char* c_line = new char[128];
	char* numbers[16];
	int lengths[16];
	char* output = new char[32];
	char* digits;
	int num, tot = 0;
	int cnt, pipe;
	int perm[7];
	bool ok;

	while(getline(cin, line)) {
		strcpy(c_line, line.c_str());
		digits = strtok(c_line, " ");
		cnt = 0;
		do {
			if (digits[0] == '|') {
				pipe = cnt;
			} else {
				numbers[cnt] = digits;
				lengths[cnt] = strlen(digits);
				for (int i = 0; i < lengths[cnt]; i++) {
					numbers[cnt][i] -= 'a';
				}
				cnt++;
			}
		} while ((digits = strtok(NULL, " ")));

		iota(perm, perm + 7, 0);
		do {
			ok = true;
			for (int i = 0; i < cnt; i++) {
				if (get_number(numbers[i], lengths[i], perm) == -1) {
					ok = false;
					break;
				}
			}

			if (ok) {
				num = 0;
				for (int i = pipe; i < cnt; i++) {
					num *= 10;
					num += get_number(numbers[i], lengths[i], perm);
				}
				tot += num;
				break;
			}
		} while(next_permutation(perm, perm + 7));
	}

	delete[] c_line;
	delete[] output;
	cout << tot << endl;
	return 0;
}
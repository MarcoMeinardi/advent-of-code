#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> nums = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

int main ()
{
	int tot = 0;
	string line;
	while (cin >> line) {
		size_t first_digit = line.find_first_of("0123456789");
		size_t last_digit = line.find_last_of("0123456789");
		size_t first_number = -1;
		size_t last_number = 0;
		int first_number_val = -1;
		int last_number_val = -1;

		int first, last;
		for (auto& [number, value] : nums) {
			size_t number_index;
			number_index = line.find(number);
			if (number_index < first_number) {
				first_number = number_index;
				first_number_val = value;
			}
			number_index = line.rfind(number);
			if (number_index != string::npos && (number_index > last_number || last_number_val == -1)) {
				last_number = number_index;
				last_number_val = value;
			}
		}
		if (first_number_val == -1) {
			assert(first_digit != string::npos);
			first = line[first_digit] - '0';
			last = line[last_digit] - '0';
		} else {
			if (first_digit == string::npos || first_number < first_digit) {
				first = first_number_val;
			} else {
				first = line[first_digit] - '0';
			}
			if (last_digit == string::npos || last_number > last_digit) {
				last = last_number_val;
			} else {
				last = line[last_digit] - '0';
			}
		}
		tot += first * 10 + last;
	}

	cout << tot << endl;
}

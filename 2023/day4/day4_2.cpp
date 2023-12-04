#include <bits/stdc++.h>
using namespace std;

int main ()
{
	string line;

	size_t ind = 0;
	vector <uint64_t> copies;

	while (getline(cin, line)) {
		if (ind >= copies.size()) {
			copies.push_back(0);
		}
		uint64_t mult = ++copies[ind];

		char* c_line = line.data();
		char* token = strtok(c_line, " ");
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");

		set<int> winning;

		while (*token != '|') {
			if (!*token) continue;
			winning.insert(atoi(token));
			token = strtok(NULL, " ");
		}

		size_t matches = 0;
		while ((token = strtok(NULL, " ")) != NULL) {
			if (!*token) continue;
			int num = atoi(token);
			auto it = winning.find(num);
			if (it != winning.end()) {
				matches++;
				winning.erase(it);
			}
		}

		for (size_t i = ind + 1, j = 0; j < matches; i++, j++) {
			if (i >= copies.size()) {
				copies.push_back(0);
			}
			copies[i] += mult;
		}
		ind++;
	}

	cout << accumulate(copies.begin(), copies.end(), 0) << endl;
}

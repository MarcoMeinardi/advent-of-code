#include <bits/stdc++.h>
using namespace std;

int main ()
{
	string line;
	uint64_t tot = 0;

	while (getline(cin, line)) {
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

		uint64_t val = 1;
		while ((token = strtok(NULL, " ")) != NULL) {
			if (!*token) continue;
			int num = atoi(token);
			auto it = winning.find(num);
			if (it != winning.end()) {
				val <<= 1;
				winning.erase(it);
			}
		}
		tot += val >> 1;
	}

	cout << tot << endl;
}

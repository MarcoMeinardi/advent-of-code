#include <bits/stdc++.h>
using namespace std;

int main () {
	string line;
	char* output = new char [32];
	char* digits;
	int len, tot = 0;

	while(getline(cin, line)) {
		strcpy(output, line.substr(line.find_first_of('|') + 2).c_str());

		digits = strtok(output, " ");
		do {
			len = strlen(digits);
			tot += (len >= 2 && len <= 4) || len == 7;
		} while ((digits = strtok(NULL, " ")));
	}
	delete[] output;

	cout << tot << endl;
	return 0;
}
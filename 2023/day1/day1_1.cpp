#include <bits/stdc++.h>
using namespace std;

int main ()
{
	int tot = 0;
	string line;
	while (cin >> line) {
		char first = line[line.find_first_of("0123456789")];
		char last = line[line.find_last_of("0123456789")];
		tot += (first - '0') * 10 + (last - '0');
	}

	cout << tot << endl;
}

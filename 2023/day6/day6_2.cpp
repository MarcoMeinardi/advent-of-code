#include <bits/stdc++.h>
using namespace std;

int main ()
{
	string line;
	string foo;

	cin >> foo;
	getline(cin, line);
	string number_str;
	copy_if(line.begin(), line.end(), back_inserter(number_str), [](char c) { return !isspace(c); });
	uint64_t time = stoull(number_str);

	cin >> foo;
	getline(cin, line);
	number_str.clear();
	copy_if(line.begin(), line.end(), back_inserter(number_str), [](char c) { return !isspace(c); });
	uint64_t dist = stoull(number_str);

	// dist = hold * (time - hold)
	// hold^2 - time * hold > dist
	uint64_t sol1 = (time + sqrt(time * time - 4 * dist)) / 2;
	uint64_t sol2 = (time - sqrt(time * time - 4 * dist)) / 2;
	if (sol1 * (time - sol1) <= dist) sol1--;
	if (sol2 * (time - sol2) <= dist) sol2++;

	cout << (sol1 - sol2 + 1) << endl;
}

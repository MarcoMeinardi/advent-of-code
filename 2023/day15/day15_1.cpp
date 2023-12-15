#include <bits/stdc++.h>
using namespace std;

uint8_t HASH(uint8_t* str)
{
	uint8_t res = 0;
	while (*str) {
		res = (res + *str) * 17;
		str++;
	}
	return res;
}

int main ()
{
	string line;
	cin >> line;

	char* line_ptr = strtok(line.data(), ",");
	int res = HASH((uint8_t*)line_ptr);
	while ((line_ptr = strtok(NULL, ","))) {
		res += HASH((uint8_t*)line_ptr);
	}

	cout << res << endl;
}

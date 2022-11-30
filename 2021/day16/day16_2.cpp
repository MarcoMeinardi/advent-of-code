#include <bits/stdc++.h>
using namespace std;

const string hexes[16] = {
	"0000",
	"0001",
	"0010",
	"0011",
	"0100",
	"0101",
	"0110",
	"0111",
	"1000",
	"1001",
	"1010",
	"1011",
	"1100",
	"1101",
	"1110",
	"1111"
};

void hex2bin (string& hex, string& bin) {
	bin.clear();
	for (char c : hex) {
		if (c <= '9') 
			bin += hexes[(int)c - '0'];
		else 
			bin += hexes[(int)c - 'A' + 10];
	}
}

uint64_t parse(int8_t*& bin) {
	int8_t* save;
	int id;
	int64_t new_len;
	int new_packets;
	uint64_t num = 0;
	vector <uint64_t> results;

	bin += 3;
	id = (*(bin) << 2) + (*(bin + 1) << 1) + *(bin + 2);
	bin += 3;

	if (id == 4) {
		while (*bin == 1) {
			bin++;
			for (int i = 0; i < 4; i++, bin++) {
				num <<= 1;
				num += *bin;
			}
		}
		bin++;
		for (int i = 0; i < 4; i++, bin++) {
			num <<= 1;
			num += *bin;
		}
		return num;
	}
	bin++;
	if (*(bin - 1) == 0) {
		new_len = 0;
		for (int i = 0; i < 15; i++, bin++) {
			new_len <<= 1;
			new_len += *bin;
		}
		save = bin;
		while (new_len > bin - save) {
			results.push_back(parse(bin));
		}
	} else {
		new_packets = 0;
		for (int i = 0; i < 11; i++, bin++) {
			new_packets <<= 1;
			new_packets += *bin;
		}
		while (new_packets--) {
			results.push_back(parse(bin));
		}
	}

	switch (id) {
	case 0:
		return accumulate(results.begin(), results.end(), 0ULL);
	case 1:
		return accumulate(results.begin(), results.end(), 1ULL, [] (uint64_t a, uint64_t b) { return a * b; });
	case 2:
		return *min_element(results.begin(), results.end());
	case 3:
		return *max_element(results.begin(), results.end());
	case 5:
		return results[0] > results[1];
	case 6:
		return results[0] < results[1];
	case 7:
		return results[0] == results[1];
	default:
		assert(false);
	}
}

int main () {
	string input;
	string binary;
	int8_t* bin;

	cin >> input;
	hex2bin(input, binary);
	bin = (int8_t*)binary.c_str();
	for (int i = 0; bin[i]; i++) {
		bin[i] -= '0';
	}

	cout << parse(bin) << endl;
	return 0;
}
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

int parse(int8_t*& bin) {
	int8_t* save;
	int id;
	int64_t new_len;
	int new_packets;
	int tot;

	tot = (*(bin) << 2) + (*(bin + 1) << 1) + *(bin + 2);
	bin += 3;
	id = (*(bin) << 2) + (*(bin + 1) << 1) + *(bin + 2);
	bin += 3;

	if (id == 4) {
		while (*bin == 1) {
			bin += 5;
		}
		bin += 5;
	} else {
		bin++;
		if (*(bin - 1) == 0) {
			new_len = 0;
			for (int i = 0; i < 15; i++, bin++) {
				new_len <<= 1;
				new_len += *bin;
			}
			save = bin;
			while (new_len > bin - save) {
				tot += parse(bin);
			}
		} else {
			new_packets = 0;
			for (int i = 0; i < 11; i++, bin++) {
				new_packets <<= 1;
				new_packets += *bin;
			}
			while (new_packets--) {
				tot += parse(bin);
			}
		}
	}

	return tot;
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
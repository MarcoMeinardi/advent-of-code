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

void lens_operation(char* lens, vector<list<pair<string, int>>>& boxes)
{
	int off = strcspn(lens, "=-");
	char op = lens[off];
	lens[off] = '\0';
	string label = string(lens, 0, off);
	size_t ind = HASH((uint8_t*)lens);

	if (op == '-') {
		boxes[ind].remove_if([&] (auto& box) {
			return box.first == label;
		});
	} else {
		uint64_t power = stoull(string(lens + off + 1));
		auto it = find_if(boxes[ind].begin(), boxes[ind].end(), [&] (auto& box) {
			return box.first == label;
		});
		if (it != boxes[ind].end()) {
			it->second = power;
		} else {
			boxes[ind].push_back({label, power});
		}
	}
}

int main ()
{
	string line;
	cin >> line;

	vector<list<pair<string, int>>> boxes(0x100);
	char* line_ptr = strtok(line.data(), ",");
	lens_operation(line_ptr, boxes);
	while ((line_ptr = strtok(NULL, ","))) {
		lens_operation(line_ptr, boxes);
	}

	uint64_t res = 0;
	for (size_t box_ind = 0; box_ind < boxes.size(); box_ind++) {
		uint64_t lens_ind = 0;
		for (auto& [label, power] : boxes[box_ind]) {
			res += (box_ind + 1) * ++lens_ind * power;
		}
	}

	cout << res << endl;
}

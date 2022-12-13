#include <bits/stdc++.h>
using namespace std;

struct nested_list_t {
	vector <shared_ptr <nested_list_t>> children;
	int value;
	bool is_marker;

	nested_list_t() : value(-1), is_marker(false) {}
	nested_list_t(int val) : value(val), is_marker(false) {}
};

shared_ptr <nested_list_t> build_nested_list(const string& repr, bool is_marker = false) {
	stack <shared_ptr <nested_list_t>> layers;
	shared_ptr <nested_list_t> actual;

	for (char c : repr) {
		if (!layers.empty()) actual = layers.top();
		if (c == '[') {
			layers.emplace(new nested_list_t());
		} else if (c == ']') {
			if (actual->value != -1) {
				layers.pop();
				layers.top()->children.push_back(actual);
				actual = layers.top();
			}
			layers.pop();
			if (!layers.empty()) {
				layers.top()->children.push_back(actual);
			}
		} else if (c == ',') {
			if (actual->value == -1) continue;
			layers.pop();
			layers.top()->children.push_back(actual);
		} else {
			if (actual->value == -1) {
				layers.emplace(new nested_list_t(0));
				actual = layers.top();
			}
			actual->value = actual->value * 10 + c - '0';
		}
	}

	if (is_marker) actual->is_marker = true;
	return actual;
}

#define LESS -1
#define EQUAL 0
#define GREATER 1

int operator <=> (const shared_ptr <nested_list_t>& list1, const shared_ptr <nested_list_t>& list2) {
	if (list1->value != -1 && list2->value != -1) {
		return list1->value < list2->value ? LESS : list1->value == list2->value ? EQUAL : GREATER;
	}
	if (list1->value != -1) {
		if (list2->children.empty()) return GREATER;
		int compare = list1 <=> list2->children[0];
		if (compare == EQUAL) return list2->children.size() == 1 ? EQUAL : LESS;
		else return compare;
	} else if (list2->value != -1) {
		if (list1->children.empty()) return LESS;
		int compare = list1->children[0] <=> list2;
		if (compare == EQUAL) return list1->children.size() == 1 ? EQUAL : GREATER;
		else return compare;
	} else {
		for (size_t i = 0; i < min(list1->children.size(), list2->children.size()); i++) {
			int compare = list1->children[i] <=> list2->children[i];
			if (compare != EQUAL) return compare;
		}
		return list1->children.size() < list2->children.size() ? LESS : list1->children.size() == list2->children.size() ? EQUAL : GREATER;
	}
}

bool operator < (const shared_ptr <nested_list_t>& list1, const shared_ptr <nested_list_t>& list2) {
	return list1 <=> list2 == LESS;
}

int main () {
	string line;
	vector <shared_ptr <nested_list_t>> packets;

	while (cin >> line) {
		packets.push_back(build_nested_list(line));
	}
	packets.push_back(build_nested_list("[[2]]", true));
	packets.push_back(build_nested_list("[[6]]", true));

	size_t result = 1;
	sort(packets.begin(), packets.end());
	for (size_t i = 0; i < packets.size(); i++) {
		if (packets[i]->is_marker) {
			result *= i + 1;
		}
	}

	cout << result << endl;
}

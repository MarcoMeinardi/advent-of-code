#include <bits/stdc++.h>
using namespace std;

#define MAX_DEPTH 4

struct number {
	int val;
	int depth;

	number(int val_, int depth_): val(val_), depth(depth_) {};
};

bool explode(vector <number>& nums) {
	for (size_t i = 0; i < nums.size(); i++) {
		if (nums[i].depth == MAX_DEPTH) {
			if (i > 0) nums[i - 1].val += nums[i].val;
			if (i + 2 < nums.size()) nums[i + 2].val += nums[i + 1].val;
			nums[i].val = 0;
			nums[i].depth--;
			nums.erase(nums.begin() + i + 1);
			return true;
		}
	}
	return false;
}

bool split(vector <number>& nums) {
	for (size_t i = 0; i < nums.size(); i++) {
		if (nums[i].val > 9) {
			nums[i].depth++;
			nums.insert(nums.begin() + i + 1, (number){(int)ceil(nums[i].val / 2.0), nums[i].depth});
			nums[i].val /= 2;
			return true;
		}
	}
	return false;
}

int magnitude(vector <number>& nums) {
	int path = 0;
	int res = 0;
	int val;
	for (number& n : nums) {
		val = n.val;
		for (int i = MAX_DEPTH - 1; i >= MAX_DEPTH - n.depth - 1; i--) {
			if (path & (1 << i)) {
				val *= 2;
			} else {
				val *= 3;
			}
		}
		res += val;
		path += 1 << (MAX_DEPTH - n.depth - 1);
	}
	return res;
}

int main () {
	string line;
	vector <number> nums;
	int depth;

	cin >> line;
	depth = -1;
	for (char c : line) {
		if (c == '[') depth++;
		else if (c == ']') depth--;
		else if (c == ',') continue;
		else nums.push_back(number(c - '0', depth));
	}

	while(cin >> line) {
		for (number& n : nums) n.depth++;
		depth = 0;
		for (char c : line) {
			if (c == '[') depth++;
			else if (c == ']') depth--;
			else if (c == ',') continue;
			else nums.push_back(number(c - '0', depth));
		}

		while(explode(nums) || split(nums));
	}

	cout << magnitude(nums) << endl;
	return 0;
}
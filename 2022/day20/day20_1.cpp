#include <bits/stdc++.h>
using namespace std;

int main () {
	vector <int> nums;
	int cur;

	int ind = 0;
	int original_zero_pos = -1;
	while (cin >> cur) {
		nums.push_back(cur);
		if (cur == 0) original_zero_pos = ind;
		ind++;
	}
	assert(original_zero_pos != 0);

	int n = (int)nums.size();
	vector <int> original_pos(n);
	vector <int> actual_pos(n);
	iota(original_pos.begin(), original_pos.end(), 0);
	iota(actual_pos.begin(), actual_pos.end(), 0);

	for (int ord_ind = 0; ord_ind < n; ord_ind++) {
		int to_move = actual_pos[ord_ind];
		int to_move_ori_pos = original_pos[to_move];
		int target_num = nums[to_move];
		int target_pos = to_move + target_num;
		target_pos = (target_pos % (n - 1) + n - 1) % (n - 1);
		if (target_pos == 0) target_pos = n - 1;

		if (to_move - target_pos < 0) {
			for (int i = to_move; i < target_pos; i++) {
				nums[i] = nums[i + 1];
				original_pos[i] = original_pos[i + 1];
				actual_pos[original_pos[i + 1]]--;
			}
		} else {
			for (int i = to_move; i > target_pos; i--) {
				nums[i] = nums[i - 1];
				original_pos[i] = original_pos[i - 1];
				actual_pos[original_pos[i - 1]]++;
			}
		}
		nums[target_pos] = target_num;
		original_pos[target_pos] = to_move_ori_pos;
		actual_pos[original_pos[target_pos]] = target_pos;
	}

	int offset = actual_pos[original_zero_pos];
	int n1 = nums[(offset + 1000) % n], n2 = nums[(offset + 2000) % n], n3 = nums[(offset + 3000) % n];
	cout << (n1 + n2 + n3) << endl;
}

#include <bits/stdc++.h>
using namespace std;

#define KEY 811589153L

int main () {
	vector <int64_t> nums;
	int64_t cur;

	size_t ind = 0;
	size_t original_zero_pos = -1;
	while (cin >> cur) {
		cur *= KEY;
		nums.push_back(cur);
		if (cur == 0) original_zero_pos = ind;
		ind++;
	}
	assert(original_zero_pos != 0);

	int64_t n = (int64_t)nums.size();
	vector <size_t> original_pos(n);
	vector <size_t> actual_pos(n);
	iota(original_pos.begin(), original_pos.end(), 0UL);
	iota(actual_pos.begin(), actual_pos.end(), 0UL);

	for (size_t round = 0; round < 10; round++) {
		for (size_t ord_ind = 0; ord_ind < nums.size(); ord_ind++) {
			int64_t to_move = (int64_t)actual_pos[ord_ind];
			size_t to_move_ori_pos = original_pos[to_move];
			int64_t target_num = nums[to_move];
			int64_t target_pos = to_move + target_num;
			target_pos = (target_pos % (n - 1) + n - 1) % (n - 1);
			if (target_pos == 0) target_pos = n - 1;

			if (to_move - target_pos < 0) {
				for (int64_t i = to_move; i < target_pos; i++) {
					nums[i] = nums[i + 1];
					original_pos[i] = original_pos[i + 1];
					actual_pos[original_pos[i + 1]]--;
				}
			} else {
				for (int64_t i = to_move; i > target_pos; i--) {
					nums[i] = nums[i - 1];
					original_pos[i] = original_pos[i - 1];
					actual_pos[original_pos[i - 1]]++;
				}
			}
			nums[target_pos] = target_num;
			original_pos[target_pos] = to_move_ori_pos;
			actual_pos[original_pos[target_pos]] = target_pos;
		}
	}

	size_t offset = actual_pos[original_zero_pos];
	int64_t n1 = nums[(offset + 1000) % n], n2 = nums[(offset + 2000) % n], n3 = nums[(offset + 3000) % n];
	cout << (n1 + n2 + n3) << endl;
}

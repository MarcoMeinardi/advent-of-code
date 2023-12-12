#include <bits/stdc++.h>
using namespace std;

vector<vector<int64_t>> dp;

bool does_fit(string& springs, int num, size_t springs_ind)
{
	if (springs_ind + num > springs.size()) {
		return false;
	}
	if (springs_ind + num < springs.size() && springs[springs_ind + num] == '#') {
		return false;
	}
	for (int i = 0; i < num; i++) {
		if (springs[springs_ind + i] == '.') {
			return false;
		}
	}
	return true;
}

int64_t try_all_dp(string& springs, vector<int>& nums, size_t springs_ind=0, size_t nums_ind=0)
{
	if (springs_ind >= springs.size()) {
		return nums_ind == nums.size();
	}
	if (dp[springs_ind][nums_ind] != -1) {
		return dp[springs_ind][nums_ind];
	}

	int64_t res = 0;

	if (springs[springs_ind] == '.') {
		res = try_all_dp(springs, nums, springs_ind + 1, nums_ind);
	} else if (springs[springs_ind] == '?') {
		if (nums_ind < nums.size() && does_fit(springs, nums[nums_ind], springs_ind)) {
			res += try_all_dp(springs, nums, springs_ind + nums[nums_ind] + 1, nums_ind + 1);
		}
		res += try_all_dp(springs, nums, springs_ind + 1, nums_ind);
	} else {
		if (nums_ind < nums.size() && does_fit(springs, nums[nums_ind], springs_ind)) {
			res = try_all_dp(springs, nums, springs_ind + nums[nums_ind] + 1, nums_ind + 1);
		}
	}

	dp[springs_ind][nums_ind] = res;
	return res;
}

int main ()
{
	string springs;
	string str_nums;
	uint64_t tot = 0;

	while (cin >> springs >> str_nums) {
		replace(str_nums.begin(), str_nums.end(), ',', ' ');
		stringstream ss(str_nums);
		vector<int> nums;
		int x;
		while (ss >> x) {
			nums.push_back(x);
		}
		string real_springs = springs;
		vector<int> real_nums;
		real_nums.reserve(nums.size() * 5);
		copy(nums.begin(), nums.end(), back_inserter(real_nums));
		for (int i = 0; i < 4; i++) {
			real_springs += "?" + springs;
			for (int i : nums) {
				real_nums.push_back(i);
			}
		}
		springs = std::move(real_springs);
		nums = std::move(real_nums);

		dp.clear();
		dp.resize(springs.size(), vector<int64_t>(nums.size() + 1, -1));
		int64_t line_res = try_all_dp(springs, nums);
		tot += line_res;
	}

	cout << tot << endl;
}


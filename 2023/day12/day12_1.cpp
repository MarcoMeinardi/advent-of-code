#include <bits/stdc++.h>
using namespace std;


bool check_possible(string& springs, vector<int>& nums)
{
	size_t nums_ind = 0;
	int acc = 0;
	for (size_t spring_ind = 0; spring_ind < springs.size(); spring_ind++) {
		if (springs[spring_ind] == '#') {
			acc++;
		} else if (springs[spring_ind] == '.') {
			if (acc) {
				if (nums_ind == nums.size() || acc != nums[nums_ind]) {
					return false;
				}
				acc = 0;
				nums_ind++;
			}
		}
	}
	return (nums_ind == nums.size() && acc == 0) || (nums_ind == nums.size()-1 && acc == nums[nums_ind]);
}

uint64_t try_all(string& springs, vector<int>& nums, size_t ind=0)
{
	if (ind == springs.size()) {
		return check_possible(springs, nums);
	}

	uint64_t res = 0;
	if (springs[ind] == '?') {
		springs[ind] = '.';
		res += try_all(springs, nums, ind+1);
		springs[ind] = '#';
		res += try_all(springs, nums, ind+1);
		springs[ind] = '?';
	} else {
		res += try_all(springs, nums, ind+1);
	}
	return res;
}

int main ()
{
	string line;
	string str_nums;
	uint64_t tot = 0;


	while (cin >> line >> str_nums) {
		replace(str_nums.begin(), str_nums.end(), ',', ' ');
		stringstream ss(str_nums);
		vector<int> nums;
		int x;
		while (ss >> x) {
			nums.push_back(x);
		}

		tot += try_all(line, nums);
	}

	cout << tot << endl;
}

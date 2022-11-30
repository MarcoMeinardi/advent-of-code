#include <bits/stdc++.h>
using namespace std;

int bin2int (string& num) {
	int tot = 0;
	for (char d : num) {
		tot <<= 1;
		tot += d == '1';
	}
	return tot;
}

int get_rating (list <string>& nums, int pos, bool oxygen) {
	if(nums.size() == 1) {
		return bin2int(nums.front());
	}
	unsigned int count = 0;
	bool win;

	for (string num : nums) {
		count += (num[pos] == '1');
	}
	win = oxygen ? count >= nums.size() / 2.0 : count < nums.size() / 2.0;
	nums.remove_if([&] (string num) {return (num[pos] == '0') == win;});
	return get_rating(nums, pos + 1, oxygen);
}

int main () {
	list <string> nums1, nums2;
	string digits;
	int oxygen, co2;
	

	while (cin >> digits) {
		nums1.push_front(digits);
		nums2.push_front(digits);
	}

	oxygen = get_rating(nums1, 0, true);
	co2 = get_rating(nums2, 0, false);

	cout << (oxygen * co2) << endl;
	return 0;
}
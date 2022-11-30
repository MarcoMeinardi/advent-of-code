#include <bits/stdc++.h>
using namespace std;

bool collide (array <int64_t, 7>& solid, array <int64_t, 7>& empty) {
	if (empty[0] > solid[1] || empty[1] < solid[0]) return false;
	if (empty[2] > solid[3] || empty[3] < solid[2]) return false;
	if (empty[4] > solid[5] || empty[5] < solid[4]) return false;
	return true;
}

vector <array <int64_t, 7>> split (array <int64_t, 7>& solid, array <int64_t, 7>& empty) {
	vector <array <int64_t, 7>> sub_volumes;
	int64_t save;

	for (int i = 0; i < 6; i++) {
		if (((i & 1) == 0 && empty[i] > solid[i]) || ((i & 1) == 1 && empty[i] < solid[i])) {
			save = solid[i ^ 1];
			solid[i ^ 1] = empty[i] + ((i & 1) == 0 ? -1LL : +1LL);
			sub_volumes.push_back(solid);
			solid[i ^ 1] = save;
			solid[i] = empty[i];
		}
	}

	return sub_volumes;
}

int64_t get_volume(vector <array <int64_t, 7>>& volumes, array <int64_t, 7>& volume, size_t check_start) {
	int64_t tot = 0;
	for (size_t i = check_start; i < volumes.size(); i++) {
		if (collide(volume, volumes[i])) {
			for (array <int64_t, 7>& sub_volume : split(volume, volumes[i])) {
				tot += get_volume(volumes, sub_volume, i + 1);
			}
			return tot;
		}
	}
	return (volume[1] - volume[0] + 1LL) * (volume[3] - volume[2] + 1LL) * (volume[5] - volume[4] + 1LL);
}

int main () {
	char oo[4];
	int x1, x2, y1, y2, z1, z2;
	vector <array <int64_t, 7>> volumes;
	int64_t tot = 0;

	while(scanf("%s x=%d..%d,y=%d..%d,z=%d..%d", oo, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
		volumes.push_back({(int64_t)x1, (int64_t)x2, (int64_t)y1, (int64_t)y2, (int64_t)z1, (int64_t)z2, oo[1] == 'n'});
	}

	for (size_t i = 0; i < volumes.size(); i++) {
		if (volumes[i][6]) {
			tot += get_volume(volumes, volumes[i], i + 1);
		}
	}

	cout << tot << endl;
	return 0;
}
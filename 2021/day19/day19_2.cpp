#include <bits/stdc++.h>
using namespace std;

struct point {
	int x, y, z;
	bool is_scanner;

	point() {};
	point(int x_, int y_, int z_, bool is_scanner_): x(x_), y(y_), z(z_), is_scanner(is_scanner_) {};
	bool operator == (point& other) {
		return x == other.x && y == other.y && z == other.z;
	}

	void print() {
		cout << "(" << x << ", " << y << ", " << z << ")" << endl;
	}

	point inv() {
		return point(-x, -y, -z, false);
	}
};


int overlapping(vector <point>& a, vector <point>& b) {
	int tot = 0;
	for (point& pa : a) {
		for (point& pb : b) {
			tot += pa == pb && !pa.is_scanner && !pb.is_scanner;
		}
	}
	return tot;
}

void translate(vector <point>& a, point reference) {
	for (point& p : a) {
		p.x -= reference.x;
		p.y -= reference.y;
		p.z -= reference.z;
	}
}

void rotate_x(vector <point>& points) {
	int c;
	for (point& p : points) {
		c = p.y;
		p.y = -p.z;
		p.z = c;
	}
}

void rotate_y(vector <point>& points) {
	int c;
	for (point& p : points) {
		c = p.x;
		p.x = -p.z;
		p.z = c;
	}
}

void rotate_z(vector <point>& points) {
	int c;
	for (point& p : points) {
		c = p.x;
		p.x = -p.y;
		p.y = c;
	}
}


void rotate(vector <point>& a, int rotation) {
	switch(rotation) {
	case 0: 
	case 1:
	case 2:
	case 8:
	case 9:
	case 10:
		rotate_x(a);
		break;
	case 3:
	case 11:
		rotate_x(a), rotate_z(a);
		break;
	case 4:
	case 5:
	case 6:
	case 12:
	case 13:
	case 14:
		rotate_y(a);
		break;
	case 7:
		rotate_y(a);
		rotate_z(a);
		break;
	case 15:
		rotate_y(a);
		rotate_z(a);
		rotate_y(a);
		break;
	case 16:
	case 17:
	case 18:
	case 20:
	case 21:
	case 22:
		rotate_z(a);
		break;
	case 19:
		rotate_z(a);
		rotate_x(a);
		rotate_x(a);
		break;
	case 23:
		rotate_z(a);
		rotate_y(a);
		rotate_x(a);
		rotate_x(a);
		break;
	default:
		assert(false);
	}
}

bool match(vector <point>& a, vector <point>& b, vector <point>& scanner_positions) {
	int matches;
	point inverse;
	for (int r = 0; r < 24; r++) {
		for (size_t i = 0; i < a.size(); i++) {
			for (size_t j = 0; j < b.size(); j++) {
				if (a[i].is_scanner || b[j].is_scanner) continue;

				inverse = a[i].inv();
				translate(a, a[i]);
				translate(b, b[j]);
				matches = overlapping(a, b);
				translate(a, inverse);
				if (matches >= 12) {
					translate(b, inverse);
					scanner_positions.push_back(b[0]);
					return true;
				}
			}
		}
		rotate(b, r);
	}
	return false;
}

int distance(point& a, point& b) {
	return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

int main () {
	vector <vector <point>> scanner;
	int x, y, z;
	char foo[0x100];
	vector <bool> done, todo;
	bool any;
	vector <point> scanner_positions;
	int res;

	while(scanf("%[^\n]", foo) == 1) {
		scanner.push_back({point(0, 0, 0, true)});
		while(scanf("%d,%d,%d", &x, &y, &z) == 3) {
			scanner.back().emplace_back(x, y, z, false);
		}
	}
	done.resize(scanner.size());
	todo.resize(scanner.size());
	todo[0] = true;
	scanner_positions.push_back(scanner[0][0]);

	do {
		for (size_t i = 0; i < scanner.size(); i++) {
			if (!todo[i]) continue;

			for (size_t j = 0; j < scanner.size(); j++) {
				if (done[j] || todo[j]) continue;

				if (match(scanner[i], scanner[j], scanner_positions)) {
					todo[j] = true;
				}
			}
			done[i] = true, todo[i] = false;
		}

		any = false;
		for (size_t i = 0; i < scanner.size(); i++) {
			if (!done[i]) {
				any = true;
				break;
			}
		}
	} while(any);

	res = 0;
	for (size_t i = 0; i < scanner_positions.size() - 1; i++) {
		for (size_t j = i + 1; j < scanner_positions.size(); j++) {
			res = max(res, distance(scanner_positions[i], scanner_positions[j]));
		}
	}

	cout << res << endl;
	return 0;
}
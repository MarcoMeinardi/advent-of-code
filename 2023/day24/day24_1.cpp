#include <bits/stdc++.h>
using namespace std;

#define AREA_START (200000000000000.0)
#define AREA_END (400000000000000.0)

struct point_t {
	double x, y;
};

struct line_t {
	double m, q;
};

#define SGN(x) (assert((x) != 0), (x) < 0 ? -1 : 1)

struct hail_t {
	point_t p;
	point_t v;
	line_t t;

	// y = mx + q
	hail_t(double px, double py, __attribute__((unused)) double pz, double vx, double vy, __attribute__((unused)) double vz)
	{
		p.x = px;
		p.y = py;
		v.x = vx;
		v.y = vy;

		t.m = vy / vx;
		t.q = py - t.m * px;
	}
};

bool intersect(hail_t& a, hail_t& b)
{
	// m1*x + q1 = m2*x + q2
	double x = (b.t.q - a.t.q) / (a.t.m - b.t.m);
	point_t i = {
		x,
		a.t.m * x + a.t.q
	};
	if (
		SGN(a.v.x) != SGN(i.x - a.p.x) || SGN(a.v.y) != SGN(i.y - a.p.y) ||
		SGN(b.v.x) != SGN(i.x - b.p.x) || SGN(b.v.y) != SGN(i.y - b.p.y))
	{
		return false;
	}

	if (i.x < AREA_START || i.x > AREA_END || i.y < AREA_START || i.y > AREA_END) {
		return false;
	}
	return true;
}

int main ()
{
	vector<hail_t> hails;
	string line;

	while (getline(cin, line)) {
		double px, py, pz, vx, vy, vz;
		sscanf(line.c_str(), "%lf, %lf, %lf @ %lf, %lf, %lf", &px, &py, &pz, &vx, &vy, &vz);

		hails.emplace_back(px, py, pz, vx, vy, vz);
	}

	int tot = 0;
	for (size_t i = 0; i < hails.size(); i++) {
		for (size_t j = i + 1; j < hails.size(); j++) {
			if (intersect(hails[i], hails[j])) {
				tot++;
			}
		}
	}

	cout << tot << endl;
}

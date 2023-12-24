#include <bits/stdc++.h>
#include <z3++.h>
using namespace std;

struct point_t {
	z3::expr x, y, z;
};

struct hail_t {
	point_t p;
	point_t v;
};

int main ()
{
	vector<hail_t> hails;
	string line;
	z3::context ctx;

	while (getline(cin, line)) {
		uint64_t px, py, pz, vx, vy, vz;
		sscanf(line.c_str(), "%ld, %ld, %ld @ %ld, %ld, %ld", &px, &py, &pz, &vx, &vy, &vz);

		hails.push_back({
			ctx.bv_val(px, 64),
			ctx.bv_val(py, 64),
			ctx.bv_val(pz, 64),
			ctx.bv_val(vx, 64),
			ctx.bv_val(vy, 64),
			ctx.bv_val(vz, 64)
		});
	}

	point_t p = {
		ctx.bv_const("px", 64),
		ctx.bv_const("py", 64),
		ctx.bv_const("pz", 64)
	};

	point_t v = {
		ctx.bv_const("vx", 64),
		ctx.bv_const("vy", 64),
		ctx.bv_const("vz", 64)
	};

	z3::solver solver(ctx);

	int cnt = 0;

	// 6 unknowns + 1 unknown for each hail and 3 equations for each hail
	for (size_t i = 0; i < 3; i++) {
		hail_t& hail = hails[i];
		char name[16];
		sprintf(name, "h%d", cnt++);
		z3::expr t = ctx.bv_const(name, 64);
		solver.add(t >= 0);
		solver.add(p.x + v.x * t == hail.p.x + hail.v.x * t);
		solver.add(p.y + v.y * t == hail.p.y + hail.v.y * t);
		solver.add(p.z + v.z * t == hail.p.z + hail.v.z * t);
	}

	z3::check_result solver_result = solver.check();
	assert(solver_result == z3::sat);

	z3::model model = solver.get_model();
	uint64_t x = model.eval(p.x).get_numeral_uint64();
	uint64_t y = model.eval(p.y).get_numeral_uint64();
	uint64_t z = model.eval(p.z).get_numeral_uint64();
	uint64_t ans = x + y + z;

	cout << ans << endl;
}

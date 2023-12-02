#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> colors = {{"red", 0}, {"green", 1}, {"blue", 2}};

int main ()
{
	int64_t tot = 0;
	string line;

	while (getline(cin, line)) {
		stringstream ss(line);
		string word;
		string foo;
		ss >> word;
		assert(word == "Game");
		int game_id;
		ss >> game_id;

		array<int64_t, 3> need = {0, 0, 0};
		bool finish = false;
		ss >> foo;
		while (!finish) {
			int64_t q;
			string color;

			ss >> q >> color;
			if (color.back() != ',' && color.back() != ';') {
				finish = true;
			} else {
				color = color.substr(0, color.size() - 1);
			}
			assert(colors.find(color) != colors.end());
			need[colors[color]] = max(need[colors[color]], q);
		}
		tot += need[0] * need[1] * need[2];
	}

	cout << tot << endl;
}

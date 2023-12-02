#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> colors = {{"red", 0}, {"green", 1}, {"blue", 2}};

int main ()
{
	int tot = 0;
	string line;

	while (getline(cin, line)) {
		stringstream ss(line);
		string word;
		string foo;
		ss >> word;
		assert(word == "Game");
		int game_id;
		ss >> game_id;

		bool finish = false;
		bool good = true;
		ss >> foo;
		while (!finish && good) {
			int q;
			string color;
			ss >> q >> color;
			if (color.back() != ',' && color.back() != ';') {
				finish = true;
			} else {
				color = color.substr(0, color.size() - 1);
			}
			assert(colors.find(color) != colors.end());
			if (q > 12 + colors[color]) {
				good = false;
			}
		}
		if (good) {
			tot += game_id;
		}
	}

	cout << tot << endl;
}

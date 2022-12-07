#include <bits/stdc++.h>
using namespace std;

struct dir_t {
	size_t size;
	unordered_map <string, dir_t*> children;
	dir_t* parent;
	unordered_map <string, size_t> files;

	dir_t(dir_t* parent) : size(0), parent(parent) {};

	size_t traverse(set <size_t>& sizes) {
		for (auto& [ignore, child] : children) {
			size += child->traverse(sizes);
		}

		for (auto& [ignore, fsize] : files) {
			size += fsize;
		}

		sizes.insert(size);

		return size;
	}
};


int main () {
	string line;
	dir_t* root = new dir_t(nullptr);

	dir_t* cwd = root;
	getline(cin, line);
	bool stop = false;
	while (!stop) {
		if (line.substr(2, 2) == "cd") {
			string where = line.substr(5);
			if (where == "/") {
				cwd = root;
			} else if (where == "..") {
				cwd = cwd->parent;
			} else {
				assert(cwd->children.find(where) != cwd->children.end());
				cwd = cwd->children[where];
			}
			getline(cin, line);

		} else {
			while (true) {

				if (getline(cin, line)) {
					if (line[0] == '$') break;
					if (line[0] == 'd') {
						string dirname = line.substr(4);
						assert(cwd->children.find(dirname) == cwd->children.end());
						cwd->children[dirname] = new dir_t(cwd);
					} else {
						size_t space = line.find_first_of(' ');
						assert(space != string::npos);
						size_t size = stoull(line.substr(0, space));
						string name = line.substr(space + 1);
						assert(cwd->files.find(name) == cwd->files.end());
						cwd->files[name] = size;
					}

				} else {
					stop = true;
					break;
				}
			}
		}
	}

	set <size_t> sizes;
	root->traverse(sizes);
	size_t free_space = 70000000ULL - root->size;

	cout << *sizes.lower_bound(30000000ULL - free_space) << endl;
}

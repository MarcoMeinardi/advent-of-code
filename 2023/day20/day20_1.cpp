#include <bits/stdc++.h>
using namespace std;

#define LOW 0
#define HIGH 1

class module_t {
public:
	ssize_t id;
	vector<ssize_t> outputs;
	virtual void parse_signal(queue<tuple<ssize_t, ssize_t, bool>>&, ssize_t, bool) {}
	virtual void add_input(int) {}

	void add_output(int output)
	{
		outputs.push_back(output);
	}

	void send_signal(queue<tuple<ssize_t, ssize_t, bool>>& work_queue, bool signal)
	{
		for (ssize_t output : outputs) {
			work_queue.emplace(output, id, signal);
		}
	}
};

class broadcaster_t : public module_t {
public:
	void parse_signal(queue<tuple<ssize_t, ssize_t, bool>>& work_queue, ssize_t, bool)
	{
		send_signal(work_queue, LOW);
	}
};

class flip_flop_t : public module_t {
public:
	bool state;

	flip_flop_t() : state(LOW) {}
	void parse_signal(queue<tuple<ssize_t, ssize_t, bool>>& work_queue, ssize_t, bool signal)
	{
		if (signal == HIGH) return;
		state = !state;
		send_signal(work_queue, state);
	}
};

class conjunction_t : public module_t {
public:
	map<int, bool> memory;

	void add_input(int id)
	{
		memory[id] = LOW;
	}

	void parse_signal(queue<tuple<ssize_t, ssize_t, bool>>& work_queue, ssize_t input, bool signal)
	{
		memory[input] = signal;
		if (all_of(memory.begin(), memory.end(), [](auto& p) { return p.second == HIGH; })) {
			send_signal(work_queue, LOW);
		} else {
			send_signal(work_queue, HIGH);
		}
	}
};

unordered_map<string, int> name2id;
ssize_t get_id(string name)
{
	if (name2id.find(name) == name2id.end()) {
		ssize_t id = name2id.size();
		name2id[name] = id;
	}
	return name2id[name];
}

void do_round(vector<unique_ptr<module_t>>& modules, ssize_t broadcaster, array<uint64_t, 2>& signals)
{
	queue<tuple<ssize_t, ssize_t, bool>> work_queue;
	work_queue.emplace(broadcaster, -1, LOW);

	while (!work_queue.empty()) {
		auto [id, from, signal] = work_queue.front();
		work_queue.pop();
		signals[signal]++;
		if (modules[id] != nullptr) {
			modules[id]->parse_signal(work_queue, from, signal);
		}
	}
}

int main ()
{
	vector<unique_ptr<module_t>> modules;
	ssize_t broadcaster = -1;
	string line;

	while (getline(cin, line)) {
		stringstream ss(line);
		string name;
		ss >> name;

		unique_ptr<module_t> new_module;
		bool is_broadcaster = false;
		if (name[0] == 'b') {
			assert(broadcaster == -1);
			new_module = make_unique<broadcaster_t>();
			is_broadcaster = true;
		} else if (name[0] == '%') {
			name = name.substr(1);
			new_module = make_unique<flip_flop_t>();
		} else if (name[0] == '&') {
			name = name.substr(1);
			new_module = make_unique<conjunction_t>();
		} else {
			assert(false);
		}
		ssize_t id = get_id(name);
		new_module->id = id;
		if (is_broadcaster) {
			broadcaster = id;
		}
		while ((ssize_t)modules.size() <= id) {
			modules.emplace_back();
		}
		modules[id] = std::move(new_module);

		ss >> name;  // ignore "->"
		while (ss >> name) {
			if (name.back() == ',') {
				name.pop_back();
			}
			ssize_t out_id = get_id(name);
			modules[id]->add_output(out_id);
		}
	}
	assert(broadcaster != -1);

	for (ssize_t input = 0; input < (ssize_t)modules.size(); input++) {
		for (ssize_t output : modules[input]->outputs) {
			if (modules[output] != nullptr) {
				modules[output]->add_input(input);
			}
		}
	}
	while (modules.size() < name2id.size()) {  // ouput nodes are real, not just for testing
		modules.emplace_back();
	}

	array<uint64_t, 2> signals = {0, 0};
	for (int round = 0; round < 1000; round++) {
		do_round(modules, broadcaster, signals);
	}

	cout << signals[0] * signals[1] << endl;
}

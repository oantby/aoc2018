#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

class Generation {
	map<int, bool> statuses;
	
	public:
	
	Generation(string in) {
		for (int i = 0; i < in.size(); i++) {
			statuses[i] = (in[i] == '#');
		}
	}
	
	Generation() {}
	
	string toString() {
		string r;
		for (const pair <const int, bool> &i : statuses) {
			r += (i.second ? '#' : '.');
		}
		return r;
	}
	
	Generation next(const map<vector<bool>, bool> &rules) {
		Generation r;
		int min = statuses.begin()->first;
		int max = statuses.rbegin()->first;
		for (const pair <const int, bool> &i : statuses) {
			if (i.first < min) min = i.first;
			if (i.first > max) max = i.first;
			vector<bool> slice;
			for (int j = -2; j < 3; j++) {
				if (statuses.count(i.first + j)) {
					slice.push_back(statuses[i.first + j]);
				} else {
					slice.push_back(false);
				}
			}
			
			if (!rules.count(slice)) {
				cerr << "invalid/incomplete ruleset. Stopping." << endl;
				for (int j = 0; j < slice.size(); j++) {
					cerr << (slice[j] ? '#' : '.');
				}
				cerr << endl;
				exit(-1);
			}
			r.statuses[i.first] = rules.at(slice);
		}
		
		{
			bool add = false;
			vector<bool> s1{
				false, false, false, false, statuses[min]
			};
			vector<bool> s2{
				false, false, false, statuses[min], statuses[min + 1]
			};
			vector<bool> s3{
				statuses[max - 1], statuses[max], false, false, false
			};
			vector<bool> s4{
				statuses[max], false, false, false, false
			};
			if (rules.at(s1)) {
				r.statuses[min - 2] = rules.at(s1);
				r.statuses[min - 1] = rules.at(s2);
			} else if (rules.at(s2)) {
				r.statuses[min - 1] = rules.at(s2);
			}
			
			if (rules.at(s4)) {
				r.statuses[max + 2] = rules.at(s4);
				r.statuses[max + 1] = rules.at(s3);
			} else if (rules.at(s3)) {
				r.statuses[max + 1] = rules.at(s3);
			}
		}
		return r;
	}
	
	uint64_t value() {
		uint64_t r = 0;
		for (const pair<const int, bool> &i : statuses) {
			if (i.second) r += i.first;
		}
		return r;
	}
};

int main(int argc, char *argv[]) {
	Generation init("##.#..#.#..#.####.#########.#...#.#.#......##.#.#...##..."
		"..#...#...#.##.#...##...#.####.##..#.#..#.");
	map<vector<bool>, bool> rules;
	rules[vector<bool>{false,false,true,false,false}] = false;
	rules[vector<bool>{false,false,true,false,true}] = false;
	rules[vector<bool>{true,false,true,false,false}] = false;
	rules[vector<bool>{false,true,false,false,true}] = false;
	rules[vector<bool>{true,false,false,false,false}] = false;
	rules[vector<bool>{false,false,false,false,true}] = false;
	rules[vector<bool>{false,true,false,true,false}] = true;
	rules[vector<bool>{true,false,true,true,true}] = false;
	rules[vector<bool>{true,true,true,true,false}] = false;
	rules[vector<bool>{false,false,false,false,false}] = false;
	rules[vector<bool>{false,true,false,false,false}] = true;
	rules[vector<bool>{true,true,true,true,true}] = true;
	rules[vector<bool>{false,true,true,true,true}] = false;
	rules[vector<bool>{true,false,false,true,false}] = true;
	rules[vector<bool>{true,false,false,false,true}] = true;
	rules[vector<bool>{false,true,true,true,false}] = false;
	rules[vector<bool>{true,true,true,false,true}] = true;
	rules[vector<bool>{false,false,false,true,true}] = true;
	rules[vector<bool>{true,false,true,true,false}] = true;
	rules[vector<bool>{false,true,false,true,true}] = true;
	rules[vector<bool>{true,true,false,true,false}] = true;
	rules[vector<bool>{false,false,false,true,false}] = false;
	rules[vector<bool>{false,false,true,true,true}] = true;
	rules[vector<bool>{true,true,true,false,false}] = true;
	rules[vector<bool>{true,true,false,false,false}] = false;
	rules[vector<bool>{false,false,true,true,false}] = false;
	rules[vector<bool>{false,true,true,false,true}] = false;
	rules[vector<bool>{true,true,false,true,true}] = false;
	rules[vector<bool>{false,true,true,false,false}] = false;
	rules[vector<bool>{true,true,false,false,true}] = true;
	rules[vector<bool>{true,false,true,false,true}] = false;
	rules[vector<bool>{true,false,false,true,true}] = true;
	
	Generation n = init;
	int ov = 0, nv = 0;
	for (uint64_t i = 0; i < 150; i++) {
		n = n.next(rules);
		ov = nv;
// 		cout << "After generation " << i << ": " << n.toString() << endl;
		nv = n.value();
// 		cout << "Value: " << nv << endl;
		cout << (nv - ov) << endl;
	}
	cout << "Final: " << (nv + (nv - ov)*(50000000000-150)) << endl;
	return 0;
}
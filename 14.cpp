#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<uint8_t> rs;

int main(int argc, char *argv[]) {
	int k = 360781;
	const vector<uint8_t> in{3,6,0,7,8,1};
	int e = 2;
	map<int, size_t> curs;
	rs = vector<uint8_t>{3, 7};
	
	for (int i = 0; i < e; i++) {
		curs[i] = i;
	}
	
	for (int i = 0; i < 50000000; i++) {
		int total = 0;
		for (int j = 0; j < e; j++) {
			total += rs[curs[j]];
			curs[j] += 1 + rs[curs[j]];
		}
		vector<uint8_t> n;
		n.push_back(total % 10);
		total /= 10;
		if (total) {
			n.push_back(total % 10);
			total /= 10;
		}
		rs.insert(rs.end(), n.rbegin(), n.rend());
		size_t count = rs.size();
		for (int j = 0; j < e; j++) {
			curs[j] %= count;
		}
	}
	auto it = search(rs.begin(), rs.end(), in.begin(), in.end());
	if (it == rs.end()) {
		cerr << "Not found" << endl;
	} else {
		cout << (it - rs.begin()) << " recipes" << endl;
	}
	return 0;
}
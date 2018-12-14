#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<uint8_t> rs;

int main(int argc, char *argv[]) {
	int k = 2018;
	int e = 2;
	map<int, size_t> curs;
	rs = vector<uint8_t>{3, 7};
	
	for (int i = 0; i < e; i++) {
		curs[i] = i;
	}
	
	while (rs.size() < k + 10) {
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
	
	for (int i = 0; i < rs.size(); i++) {
		cout << (int)rs[i];
	}
	cout << endl;
	
	return 0;
}
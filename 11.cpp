#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;



struct cell {
	int x, y, p;
	
	int calcPower(int X, int Y, int s) {
		// s is Serial
		x = X; y = Y;
		// int rackid = x + 10;
// 		// ((((x+10)*y+s)*(x+10))%1000)/100 - 5
// 		p = rackid * y;
// 		p += s;
// 		p *= rackid;
		p = ((((x+10)*y+s)*(x+10))%1000)/100 - 5;
		return p;
	}
};

struct Grid {
	vector<const cell *> cells;
	int v;
	
	void insert(const cell *c) {
		cells.push_back(c);
		
		v += c->p;
	}
	Grid() {v = 0; cells.resize(9);}
};

int main(int argc, char *argv[]) {
	cell grid[90000];
	int serial = 9995;
	
	map<pair<int,int>,Grid> grids;
	
	for (int i = 0; i < 90000; i++) {
		if (i % 300 == 0) cout << endl;
		cout << grid[i].calcPower(i%300 + 1, i/300 + 1, serial) << ' ';
	}
	cout << endl;
	
	for (int i = 0; i < 90000; i++) {
		if (grid[i].x < 2) continue;
		if (grid[i].x > 299) continue;
		if (grid[i].y < 2) continue;
		if (grid[i].y > 299) continue;
		
		pair<int,int> index = make_pair(grid[i].x - 1, grid[i].y - 1);
		grids[index].insert(grid + i - 301);
		grids[index].insert(grid + i - 300);
		grids[index].insert(grid + i - 299);
		grids[index].insert(grid + i - 1);
		grids[index].insert(grid + i);
		grids[index].insert(grid + i + 1);
		grids[index].insert(grid + i + 299);
		grids[index].insert(grid + i + 300);
		grids[index].insert(grid + i + 301);
	}
	
	int max_val = -1;
	pair<int, int> winner;
	for (const pair<const pair<int, int>, Grid> &i : grids) {
		if (i.second.v > max_val) {
			max_val = i.second.v;
			winner = i.first;
		}
	}
	
	cout << "Winner grid starts at " << winner.first << ", " << winner.second << endl;
	cout << "Value: " << max_val << endl;
	
	return 0;
}
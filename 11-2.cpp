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
	Grid() {v = 0;}
};

int main(int argc, char *argv[]) {
	cell grid[90000];
	int serial = 9995;
	
	map<tuple<int,int,int>,Grid> grids;
	
	for (int i = 0; i < 90000; i++) {
		if (i % 300 == 0) cout << endl;
		cout << grid[i].calcPower(i%300 + 1, i/300 + 1, serial) << ' ';
	}
	cout << endl;
	
	for (int j = 0; j < 30; j++) {
		// j is the size of the grid; 1x1 through 300x300
		// except it goes from 0 to 299 because I want it to.
		for (int i = 0; i < 90000; i++) {
			if (grid[i].x + j > 300) continue;
			if (grid[i].y + j > 300) continue;
			
			cout << "Checking start at " << i << " with radius " << (j + 1) << endl;
			
			tuple<int,int,int> index = make_tuple(grid[i].x, grid[i].y, j + 1);
			
			grids[index].insert(grid + i);
			for (int k = 0; k <= j; k++) {
				for (int l = 0; l <= j; l++) {
					if (!k && !l) continue;
					grids[index].insert(grid + i + (k*300) + l);
				}
			}
		}
	}
	
	int max_val = -1;
	tuple<int, int, int> winner;
	for (const pair<const tuple<int, int, int>, Grid> &i : grids) {
		if (i.second.v > max_val) {
			max_val = i.second.v;
			winner = i.first;
		}
	}
	
	cout << "Winner: " << get<0>(winner) << ',' << get<1>(winner) << ',' << get<2>(winner) << endl;
	cout << "Value: " << max_val << endl;
	
	return 0;
}


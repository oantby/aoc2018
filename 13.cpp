#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <set>

using namespace std;

void draw();
void step();

struct Cart {
	uint8_t turnTicker = 0;
	uint8_t curDir;
	#define DIR_UP 1
	#define DIR_DOWN 2
	#define DIR_LEFT 3
	#define DIR_RIGHT 4
	
	char type() {
		switch (curDir) {
			case DIR_UP:
				return '^';
				break;
			case DIR_DOWN:
				return 'v';
				break;
			case DIR_RIGHT:
				return '>';
				break;
			case DIR_LEFT:
				return '<';
				break;
		}
		return 'I';
	}
	
	Cart(char dir) {
		switch (dir) {
			case '^':
				curDir = DIR_UP;
				break;
			case 'v':
				curDir = DIR_DOWN;
				break;
			case '>':
				curDir = DIR_RIGHT;
				break;
			case '<':
				curDir = DIR_LEFT;
				break;
		}
	}
};

struct Crash {
	string message;
	int row, col;
	
	Crash(int r, int c) {
		row = r;
		col = c;
		message = "Crash occurred at (X,Y) coordinate (";
		message += to_string(col);
		message += ',';
		message += to_string(row);
		message += ')';
	}
};

struct Track {
	uint8_t type;
	Cart *cart = NULL;
	Track *up = NULL, *down = NULL, *left = NULL, *right = NULL;
	
	
};

map<int, map<int, Track> > tracks;
set<Cart *> carts;

int main(int argc, char *argv[]) {
	ifstream f;
	f.open("13in.txt", ios::in);
	if (!f) {
		cerr << "Couldn't open file. Exiting" << endl;
		return 1;
	}
	string s;
	int i = 0;
	while ((getline(f, s))) {
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == ' ') continue;
			if (s[j] == '<' || s[j] == '>') {
				tracks[i][j].type = '-';
				tracks[i][j].cart = new Cart(s[j]);
				carts.insert(tracks[i][j].cart);
				tracks[i][j - 1].right = &tracks[i][j];
				tracks[i][j].left = &tracks[i][j - 1];
			} else if (s[j] == 'v' || s[j] == '^') {
				tracks[i][j].type = '|';
				tracks[i][j].cart = new Cart(s[j]);
				carts.insert(tracks[i][j].cart);
				tracks[i - 1][j].down = &tracks[i][j];
				tracks[i][j].up = &tracks[i - 1][j];
			} else if (s[j] == '|') {
				tracks[i][j].type = '|';
				tracks[i - 1][j].down = &tracks[i][j];
				tracks[i][j].up = &tracks[i - 1][j];
			} else if (s[j] == '-') {
				tracks[i][j].type = '-';
				tracks[i][j - 1].right = &tracks[i][j];
				tracks[i][j].left = &tracks[i][j - 1];
			} else if (s[j] == '/') {
				tracks[i][j].type = '/';
				if (tracks[i].count(j - 1) && (tracks[i][j - 1].type == '-'
					|| tracks[i][j - 1].type == '+')) {
					tracks[i][j - 1].right = &tracks[i][j];
					tracks[i - 1][j].down = &tracks[i][j];
					tracks[i][j].left = &tracks[i][j - 1];
					tracks[i][j].up = &tracks[i - 1][j];
				}
			} else if (s[j] == '\\') {
				tracks[i][j].type = '\\';
				if (tracks[i].count(j - 1) && (tracks[i][j - 1].type == '-'
					|| tracks[i][j - 1].type == '+')) {
					tracks[i][j - 1].right = &tracks[i][j];
					tracks[i][j].left = &tracks[i][j - 1];
				} else if (tracks.count(i - 1) && tracks[i - 1].count(j)
					&& (tracks[i - 1][j].type == '|' || tracks[i - 1][j].type == '+')) {
					tracks[i - 1][j].down = &tracks[i][j];
					tracks[i][j].up = &tracks[i - 1][j];
				}
			} else if (s[j] == '+') {
				tracks[i][j].type = '+';
				tracks[i - 1][j].down = &tracks[i][j];
				tracks[i][j].up = &tracks[i - 1][j];
				tracks[i][j - 1].right = &tracks[i][j];
				tracks[i][j].left = &tracks[i][j - 1];
			} else {
				cerr << "AAAAAHHHHHHHHH" << endl;
				exit(-1);
			}
		}
		i++;
	}
	
	int cCount, n;
	cCount = n = carts.size();
	for (i = 0; i > -1; i++) {
		step();
		n = carts.size();
		if (n != cCount) {
			cCount = n;
			cout << "Reduced to " << cCount << " carts" << endl;
		}
		if (carts.size() == 1) {
			break;
		}
	}
	
	bool gotIt = false;
	for (i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			if (tracks[i][j].cart) {
				cout << "Last cart is at " << j << ',' << i << endl;
				gotIt = true;
				break;
			}
		}
		if (gotIt) break;
	}
	
	
	return 0;
}

void step() {
	set<Cart *> moved; // prevent from accidentally moving a cart twice.
	const map<uint8_t, uint8_t> s_translations{
		{DIR_UP, DIR_RIGHT},
		{DIR_DOWN, DIR_LEFT},
		{DIR_LEFT, DIR_DOWN},
		{DIR_RIGHT, DIR_UP}
	};
	const map<uint8_t, uint8_t> b_translations{
		{DIR_UP, DIR_LEFT},
		{DIR_DOWN, DIR_RIGHT},
		{DIR_LEFT, DIR_UP},
		{DIR_RIGHT, DIR_DOWN}
	};
	const map<uint8_t, uint8_t> l_turn {
		{DIR_UP, DIR_LEFT},
		{DIR_DOWN, DIR_RIGHT},
		{DIR_LEFT, DIR_DOWN},
		{DIR_RIGHT, DIR_UP}
	};
	const map<uint8_t, uint8_t> r_turn {
		{DIR_UP, DIR_RIGHT},
		{DIR_DOWN, DIR_LEFT},
		{DIR_LEFT, DIR_UP},
		{DIR_RIGHT, DIR_DOWN}
	};
	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			if (!tracks[i].count(j)) continue;
			if (!tracks[i][j].cart) continue;
			Cart *c = tracks[i][j].cart;
			
			if (moved.count(c)) continue;
			
			Track *newSpot = NULL;
			int newi, newj;
			switch (tracks[i][j].cart->curDir) {
				case DIR_UP:
					newSpot = tracks[i][j].up;
					newi = i - 1;
					newj = j;
					break;
				case DIR_DOWN:
					newSpot = tracks[i][j].down;
					newi = i + 1;
					newj = j;
					break;
				case DIR_LEFT:
					newSpot = tracks[i][j].left;
					newi = i;
					newj = j - 1;
					break;
				case DIR_RIGHT:
					newSpot = tracks[i][j].right;
					newi = i;
					newj = j + 1;
					break;
			}
			if ((newSpot->cart)) {
				carts.erase(newSpot->cart);
				carts.erase(c);
				delete newSpot->cart;
				newSpot->cart = NULL;
				delete c;
				tracks[i][j].cart = NULL;
				continue;
			}
			
			newSpot->cart = tracks[i][j].cart;
			tracks[i][j].cart = NULL;
			
			// determine cart's new direction.
			switch (newSpot->type) {
				case '|':
				case '-':
					// doesn't affect direction.
					break;
				case '/':
					c->curDir = s_translations.at(c->curDir);
					break;
				case '\\':
					c->curDir = b_translations.at(c->curDir);
					break;
				case '+':
					switch (c->turnTicker) {
						case 0: // turn left.
							c->curDir = l_turn.at(c->curDir);
							c->turnTicker++;
							break;
						case 1: // go straight.
							c->turnTicker++;
							break;
						case 2: // turn right.
							c->curDir = r_turn.at(c->curDir);
							c->turnTicker = 0;
							break;
					}
					break;
			}
			moved.insert(c);
		}
	}
}

void draw() {
	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			if (!tracks[i].count(j)) {
				cout << ' ';
				continue;
			}
			if (tracks[i][j].cart) {
				cout << tracks[i][j].cart->type();
			} else {
				cout << tracks[i][j].type;
			}
			
		}
		cout << '\n';
	}
	cout << endl;
}
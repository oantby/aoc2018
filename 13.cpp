#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

struct Cart {
	uint8_t turnTicker = 0;
	uint8_t curDir;
	uint32_t curX, curY;
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
	
	void step() {
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

struct Track {
	uint8_t type;
	Cart *cart = NULL;
	Track *up = NULL, *down = NULL, *left = NULL, *right = NULL;
	
	
};

map<int, map<int, Track> > tracks;

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
				tracks[i][j - 1].right = &tracks[i][j];
				tracks[i][j].left = &tracks[i][j - 1];
			} else if (s[j] == 'v' || s[j] == '^') {
				tracks[i][j].type = '|';
				tracks[i][j].cart = new Cart(s[j]);
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
	for (i = 0; i < 150; i++) {
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
	return 0;
}
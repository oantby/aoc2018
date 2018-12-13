#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

map<int, map<int, Track> > tracks;

struct Cart {
	uint8_t turnTicker = 0;
	uint8_t curDir;
	uint32_t curX, curY;
	#define DIR_UP 1
	#define DIR_DOWN 2
	#define DIR_LEFT 3
	#define DIR_RIGHT 4
	
	void step() {
		switch (curDir) {
			case DIR_UP:
				switch (track[curY - 1][curX]) {
					case 'v':
						
						break;
					case '^':
						
						break;
					case '>':
						
						break;
					case '<':
						
						break;
				}
				break;
			case DIR_DOWN:
				
				break;
			case DIR_LEFT:
				
				break;
			case DIR_DOWN:
				
				break;
			default:
				cerr << "Bad stuff" << endl;
				exit(-1);
		}
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

int main(int argc, char *argv[]) {
	ifstream f;
	f.open("13in.txt", ios::in);
	string s;
	int i = 0;
	while ((getline(f, s))) {
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == ' ') continue;
			if (s[j] == '<' || s[j] == '>') {
				tracks[i][j].type = '-';
				tracks[i][j].cart = new Cart(s[j]);
				if (tracks[i].count(j - 1)) {
					tracks[i][j - 1].right = &tracks[i][j];
					tracks[i][j].left = &tracks[i][j - 1];
				}
			} else if (s[j] == 'v' || s[j] == '^') {
				tracks[i][j].type = '|';
				tracks[i][j].cart = new Cart(s[j]);
				if (tracks.count(i - 1) && tracks[i - 1].count(j)) {
					tracks[i - 1][j].down = &tracks[i][j];
					tracks[i][j].up = &tracks[i - 1][j];
				}
			} else if (s[j] == '|') {
				tracks[i][j].type = '|';
				if (tracks.count(i - 1) && tracks[i - 1].count(j)) {
					tracks[i - 1][j].down = &tracks[i][j];
					tracks[i][j].up = &tracks[i - 1][j];
				}
			} else if (s[j] == '-') {
				tracks[i][j].type = '-';
				if (tracks[i].count(j - 1)) {
					tracks[i][j - 1].right = &tracks[i][j];
					tracks[i][j].left = &tracks[i][j - 1];
				}
			} else if (s[j] == '/') {
				tracks[i][j].type == '/';
				if (tracks[i].count(j - 1) && tracks[i][j - 1].type == '-') {
					tracks[i][j - 1].right = &tracks[i][j];
					tracks[i - 1][j].down = &tracks[i][j];
					tracks[i][j].left = &tracks[i][j - 1];
					tracks[i][j].up = &tracks[i - 1][j];
				}
			} else if (s[j] == '\\') {
				tracks[i][j].type == '\\';
				if (tracks.count(i - 1) && tracks[i - 1].count(j - 1)
					&& tracks[i - 1][j - 1].type == '|'
				if (tracks[i].count(j - 1) && tracks[i][j - 1].type == '-') {
					tracks[i][j - 1].right = &tracks[i][j];
					tracks[i][j].left = &tracks[i][j - 1];
				}
			} else if (s[j] == '+') {
				
			} else {
				cerr << "AAAAAHHHHHHHHH" << endl;
				exit(-1);
			}
		}
		i++;
	}
	return 0;
}
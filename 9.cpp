#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node {
	node *n = NULL;
	node *p = NULL;
	int v;
	
	node(int i) {v = i;}
	node() {}
};

int main(int argc, char *argv[]) {
	int p = 471, m = 7202600;
	node *b = NULL, *e = NULL, *c = NULL;
	
	b = new node(0);
	b->n = b;
	b->p = b;
	c = b;
	
	map<int, vector<node *> > kept;
	uint64_t scores[471] = {0};
	
	for (int i = 1; i <= m; i++) {
		// scores[(i-1)%p] is the current player.
		
		if (!(i%23)) {
			// multiple of 23. do weird things.
			kept[(i - 1)%p].push_back(new node(i));
			scores[(i - 1)%p] += i;
			node *spot = c->p->p->p->p->p->p->p;
			spot->p->n = spot->n;
			spot->n->p = spot->p;
			kept[(i - 1)%p].push_back(spot);
			scores[(i - 1)%p] += spot->v;
			c = spot->n;
			continue;
		}
		
		node *spot = c->n;
		node *n = new node(i);
		n->n = spot->n;
		n->p = spot;
		spot->n->p = n;
		spot->n = n;
		c = n;
	}
	
	uint64_t max_score = 0;
	int winner = -1;
	for (int i = 0; i < p; i++) {
		if (scores[i] > max_score) {
			max_score = scores[i];
			winner = i;
		}
	}
	
	cout << "Winner is elf at index " << winner << " with a score of " << max_score << endl;
	
	return 0;
}
#include "Digraph.h"
#include "BreadthDirectedFirstPaths.h"
#include "DirectedCycle.h"
#include <fstream>
#include <iostream>
#include <cstdio>

// Digraph test
void digraph_main() {
	using namespace std;
	ifstream inFile;
	inFile.open("tinyDG.txt");
//	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}
	Digraph G(inFile);
	Digraph H;
	H = G;
	cout << H << endl;
}

// BreadthDirectedFirstPaths test
void BDFP_main() {
	using namespace std;
	ifstream inFile;
	inFile.open("tinyDG.txt");
//	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}
	Digraph G(inFile);
	cout << G << endl;
//	int s = 3;
	int s;
	cout << "Start: ";
	cin >> s;
	BreadthFirstDirectedPaths copy(G, s);
	BreadthFirstDirectedPaths bfs;
	bfs = copy;

	for (int v = 0; v < G.V(); v++) {
		if (bfs.hasPathTo(v)) {
			printf("%d to %d (%d): ", s, v, bfs.distTo(v));
			for (int x : bfs.pathTo(v)) {
				if (x == s) cout << x;
				else		cout << "->" << x;
			}
			cout << endl;
		}
		else {
			printf("%d to %d (-):  not connected\n", s, v);
		}
	}
}

// Directed Cycle test
void DC_main() {
	using namespace std;
	ifstream inFile;
	inFile.open("tinyDG.txt");
	//	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}
	Digraph G(inFile);
	DirectedCycle finder(G);
	if (finder.hasCycle()) {
		cout << "Cycle: ";
		for (int v : finder.cycle())
			cout << v << " ";
		cout << endl;
	}
	else
		cout << "No cycle" << endl;
}

int main(int argc, char* argv[]) {
	DC_main();
	return 0;
}
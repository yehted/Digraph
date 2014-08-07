#include "Digraph.h"
#include "BreadthDirectedFirstPaths.h"
#include <fstream>
#include <iostream>
#include <cstdio>

// Digraph test
int digraph_main(int argc, char* argv[]) {
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
	return 0;
}

// BreadthDirectedFirstPaths test
int BDFP_main(int argc, char* argv[]) {
	using namespace std;
	ifstream inFile;
//	inFile.open("tinyDG.txt");
	inFile.open(argv[1]);
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
	BreadthFirstDirectedPaths bfs(G, s);
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
	return 0;
}
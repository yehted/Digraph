#include "Digraph.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
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
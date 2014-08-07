#include "Digraph.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

Digraph::Digraph() : V_(0), E_(0) {}

Digraph::Digraph(int V) : V_(V), E_(0), adj_(new Bag<int>[V]) {
	if (V < 0) throw std::invalid_argument("Number of vertices in a Digraph must be nonnegative");
}

Digraph::Digraph(std::istream& input) {
	try {		
		input >> V_;
		if (V_ < 0) throw std::invalid_argument("Number of vertices in a Digraph must be nonnegative");
		adj_ = new Bag<int>[V_];
		int E;
		input >> E;
		if (E < 0) throw std::invalid_argument("Number of edges in a Digraph must be nonnegative");
		int v, w;
		for (int i = 0; i < E; i++) {
			input >> v >> w;
			addEdge(v, w);
		}
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument: " << ia.what() << std::endl;
	}
}

Digraph::~Digraph() {
	delete[] adj_;
}

Digraph::Digraph(const Digraph& G) : V_(G.V_), E_(G.E_) {
	std::cout << "Copying Digraph" << std::endl;
	adj_ = new Bag<int>[G.V_];
	for (int v = 0; v < G.V_; v++) {
		// reverse so that adjacency list is in the same order as original
		Bag<int> reverse;
		for (int w : G.adj_[v])
			reverse.add(w);
		for (int w : reverse)
			adj_[v].add(w);
	}		
}

Digraph& Digraph::operator=(const Digraph& G) {
	std::cout << "Assigning Digraph" << std::endl;
	if (this == &G) return *this;

	// Free memory
	delete[] adj_;

	// Allocate memory
	V_ = G.V_;
	E_ = G.E_;
	Bag<int>* new_adj = new Bag<int>[G.V_];

	// Copy elements
	for (int v = 0; v < G.V_; v++) {
		// reverse so that adjacency list is in the same order as original
		Bag<int> reverse;
		for (int w : G.adj_[v])
			reverse.add(w);
		for (int w : reverse)
			new_adj[v].add(w);
	}

	// Reassign variables
	adj_ = new_adj;

	return *this;
}

int Digraph::V() const { return V_; }

int Digraph::E() const { return E_; }

void Digraph::addEdge(int v, int w) {
	if (v < 0 || v >= V_) throw std::out_of_range("vertex is out of bounds");
	if (w < 0 || w >= V_) throw std::out_of_range("vertex is out of bounds");
	adj_[v].add(w);
	E_++;
}

Bag<int>& Digraph::adj(int v) const {
	if (v < 0 || v >= V_) throw std::out_of_range("vertex is out of bounds");
	return adj_[v];
}

Digraph Digraph::reverse() {
	Digraph R(V_);
	for (int v = 0; v < V_; v++) {
		for (int w : adj_[v])
			R.addEdge(w, v);
	}
	return R;
}

std::ostream& operator<<(std::ostream& output, const Digraph& G) {
	output << G.V_ << " vertices, " << G.E_ << " edges" << std::endl;
	for (int v = 0; v < G.V_; v++) {
		output << v << ": ";
		for (int w : G.adj_[v])
			output << w << " ";
		output << std::endl;
	}
	return output;
}

// Digraph test
int digraph_test(int argc, char* argv[]) {
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
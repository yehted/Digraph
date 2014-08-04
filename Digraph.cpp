#include "Digraph.h"
#include <stdexcept>
#include <iostream>

Digraph::Digraph() : V_(0), E_(0) {}

Digraph::Digraph(int V) : V_(V), E_(0), adj_(new Bag<int>[V]) {
	if (V < 0) throw std::invalid_argument("Number of vertices in a Digraph must be nonnegative");
}

Digraph::Digraph(std::istream& input) {
	try {
		int V;
		input >> V;
		if (V < 0) throw std::invalid_argument("Number of vertices in a Digraph must be nonnegative");
		adj_ = new Bag<int>[V];
		int E;
		input >> E;
		if (E < 0) throw std::invalid_argument("Number of edges in a Digraph must be nonnegative");
		int v, w;
		for (int i = 0; i < E; i++) {
			input >> v >> w;
			addEdge(v, w);
		}
	}
	catch (std::invalid_argument ia) {
		std::cerr << "Invalid argument: " << ia.what() << std::endl;
	}
}
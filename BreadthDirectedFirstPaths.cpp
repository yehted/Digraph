#include "BreadthDirectedFirstPaths.h"
#include <limits>

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths() : 
marked_(NULL), edgeTo_(NULL), distTo_(NULL), V_(0) {}

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(const Digraph& G) :
marked_(new bool[G.V()]()), distTo_(new int[G.V()]), edgeTo_(new int[G.V()]()), V_(G.V()) {
	for (int v = 0; v < G.V(); v++)
		distTo_[v] = std::numeric_limits<int>::max();
}

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(const Digraph& G, int s) :
	marked_(new bool[G.V()]()), distTo_(new int[G.V()]), edgeTo_(new int[G.V()]()), V_(G.V()) {
	for (int v = 0; v < G.V(); v++)
		distTo_[v] = std::numeric_limits<int>::max();
	bfs(G, s);
}

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(const Digraph&G, Bag<int>& sources) :
marked_(new bool[G.V()]()), distTo_(new int[G.V()]), edgeTo_(new int[G.V()]()), V_(G.V()) {
	for (int v = 0; v < G.V(); v++)
		distTo_[v] = std::numeric_limits<int>::max();
	bfs(G, sources);
}

BreadthFirstDirectedPaths::~BreadthFirstDirectedPaths() {
//	printf("Deleting BDFP\n");
	delete[] marked_;
	delete[] edgeTo_;
	delete[] distTo_;
}

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(const BreadthFirstDirectedPaths& other) : V_(other.V_), visited_(other.visited_) {
//	printf("Copying BDFP\n");
	marked_ = new bool[V_];
	edgeTo_ = new int[V_];
	distTo_ = new int[V_];
	for (int i = 0; i < other.V_; i++) {
		marked_[i] = other.marked_[i];
		edgeTo_[i] = other.edgeTo_[i];
		distTo_[i] = other.distTo_[i];
	}
}

BreadthFirstDirectedPaths& BreadthFirstDirectedPaths::operator=(const BreadthFirstDirectedPaths& other) {
//	printf("Assigning BDFP\n");
	if (this == &other) return *this;
	V_ = other.V_;
	visited_ = other.visited_;
	
	// Free memory
	delete[] marked_;
	delete[] edgeTo_;
	delete[] distTo_;
	
	// Allocate memory
	marked_ = new bool[V_];
	edgeTo_ = new int[V_];
	distTo_ = new int[V_];

	// Copy elements
	for (int i = 0; i < other.V_; i++) {
		marked_[i] = other.marked_[i];
		edgeTo_[i] = other.edgeTo_[i];
		distTo_[i] = other.distTo_[i];
	}

	return *this;
}

void BreadthFirstDirectedPaths::bfs(const Digraph& G, int s) {
	Deque<int> q;
	marked_[s] = true;
	distTo_[s] = 0;
	q.addFirst(s);
	visited_.add(s);					// to keep track of visited vertices
	while (!q.isEmpty()) {
		int v = q.removeLast();
		for (int w : G.adj(v)) {
			if (!marked_[w]) {
				edgeTo_[w] = v;
				distTo_[w] = distTo_[v] + 1;
				marked_[w] = true;
				q.addFirst(w);
				visited_.add(w);		// to keep track of visited vertices
			}
		}
	}
}

void BreadthFirstDirectedPaths::bfs(const Digraph& G, Bag<int>& sources) {
	Deque<int> q;
	for (int s : sources) {
		marked_[s] = true;
		distTo_[s] = 0;
		q.addFirst(s);
		visited_.add(s);				// to keep track of visited vertices
	}	
	while (!q.isEmpty()) {
		int v = q.removeLast();
		for (int w : G.adj(v)) {
			if (!marked_[w]) {
				edgeTo_[w] = v;
				distTo_[w] = distTo_[v] + 1;
				marked_[w] = true;
				q.addFirst(w);
				visited_.add(w);		// to keep track of visited vertices
			}
		}
	}
}

void BreadthFirstDirectedPaths::reset() {
	for (int v : visited_) {
		marked_[v] = false;
		edgeTo_[v] = 0;
		distTo_[v] = std::numeric_limits<int>::max();
	}
	visited_.clear();
}

void BreadthFirstDirectedPaths::search(const Digraph& G, int s) {
	if (G.V() != V_) throw std::invalid_argument("Digraphs not the same size");
	reset();
	bfs(G, s);
}

void BreadthFirstDirectedPaths::search(const Digraph& G, Bag<int>& sources) {
	if (G.V() != V_) throw std::invalid_argument("Digraphs not the same size");
	reset();
	bfs(G, sources);
}

bool BreadthFirstDirectedPaths::hasPathTo(int v) {
	return marked_[v];
}

int BreadthFirstDirectedPaths::distTo(int v) {
	return distTo_[v];
}

Deque<int> BreadthFirstDirectedPaths::pathTo(int v) {
	if (!hasPathTo(v)) return Deque<int>();
	Deque<int> path;
	int x;
	for (x = v; distTo_[x] != 0; x = edgeTo_[x])
		path.addFirst(x);
	path.addFirst(x);
	return path;
}
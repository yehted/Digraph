#include "DirectedCycle.h"
#include <fstream>
#include <iostream>

DirectedCycle::DirectedCycle() {}

DirectedCycle::DirectedCycle(const Digraph& G) :
marked_(new bool[G.V()]()), onStack_(new bool[G.V()]()), edgeTo_(new int[G.V()]()), V_(G.V()) {
	for (int v = 0; v < V_; v++)
		if (!marked_[v]) dfs(G, v);
}

DirectedCycle::~DirectedCycle() {
	delete[] marked_;
	delete[] edgeTo_;
	delete[] onStack_;
}

DirectedCycle::DirectedCycle(const DirectedCycle& other) :
marked_(new bool[other.V_]()), onStack_(new bool[other.V_]()), edgeTo_(new int[other.V_]()), cycle_(other.cycle_), V_(other.V_) {
	for (int i = 0; i < V_; i++) {
		marked_[i] = other.marked_[i];
		edgeTo_[i] = other.edgeTo_[i];
		onStack_[i] = other.onStack_[i];
	}
}

DirectedCycle& DirectedCycle::operator=(const DirectedCycle& other) {
	if (&other == this) return *this;
	
	// Free memory
	delete[] marked_;
	delete[] edgeTo_;
	delete[] onStack_;

	// Allocate new memory
	bool* tmarked = new bool[other.V_]();
	int* tedgeTo = new int[other.V_]();
	bool* tonStack = new bool[other.V_];
	
	// Copy elements
	for (int i = 0; i < other.V_; i++) {
		marked_[i] = other.marked_[i];
		edgeTo_[i] = other.edgeTo_[i];
		onStack_[i] = other.onStack_[i];
	}

	// Reassign variables
	V_ = other.V_;
	marked_ = tmarked;
	edgeTo_ = tedgeTo;
	onStack_ = tonStack;
	cycle_ = other.cycle_;

	return *this;
}

void DirectedCycle::dfs(const Digraph& G, int v) {
	onStack_[v] = true;
	marked_[v] = true;
	for (int w : G.adj(v)) {

		// short circuit if directed cycle found
		if (cycle_.size() != 0) return;

		// found new vertex, so recur
		else if (!marked_[w]) {
			edgeTo_[w] = v;
			dfs(G, w);
		}

		// trace back directed cycle
		else if (onStack_[w]) {
			for (int x = v; x != w; x = edgeTo_[x]) {
				cycle_.addFirst(x);
			}
			cycle_.addFirst(w);
			cycle_.addFirst(v);
		}
	}
	onStack_[v] = false;
}

bool DirectedCycle::hasCycle() {
	return cycle_.size() != 0;
}

Deque<int> DirectedCycle::cycle() {
	return cycle_;
}

bool DirectedCycle::check(const Digraph& G) {
	if (hasCycle()) {
		// verify cycle
		int first = -1, last = -1;
		for (int v : cycle_) {
			if (first == -1) first = v;
			last = v;
		}
		if (first != last) {
			printf("cycle begins with %d and ends with %d\n", first, last);
			return false;
		}
	}
	return true;
}
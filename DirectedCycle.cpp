#include "DirectedCycle.h"
#include <fstream>
#include <iostream>

DirectedCycle::DirectedCycle() {}

DirectedCycle::DirectedCycle(const Digraph& G) :
marked_(new bool[G.V()]()), onStack_(new bool[G.V()]()), edgeTo_(new int[G.V()]()) {
	for (int v = 0; v < G.V(); v++)
		if (!marked_[v]) dfs(G, v);
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
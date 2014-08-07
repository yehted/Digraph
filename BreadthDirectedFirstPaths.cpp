#include "BreadthDirectedFirstPaths.h"


BreadthFirstDirectedPaths::BreadthFirstDirectedPaths() {}

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(const Digraph& G, int s) :
	marked_(new bool[G.V()]()), distTo_(new int[G.V()]), edgeTo_(new int[G.V()]()) {
	for (int v = 0; v < G.V(); v++)
		distTo_[v] = INFINITY;
	bfs(G, s);
}

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(const Digraph&G, Bag<int>& sources) :
marked_(new bool[G.V()]()), distTo_(new int[G.V()]), edgeTo_(new int[G.V()]()) {
	for (int v = 0; v < G.V(); v++)
		distTo_[v] = INFINITY;
	bfs(G, sources);
}

void BreadthFirstDirectedPaths::bfs(const Digraph& G, int s) {
	Deque<int> q;
	marked_[s] = true;
	distTo_[s] = 0;
	q.addFirst(s);
	while (!q.isEmpty()) {
		int v = q.removeLast();
		for (int w : G.adj(v)) {
			if (!marked_[w]) {
				edgeTo_[w] = v;
				distTo_[w] = distTo_[v] + 1;
				marked_[w] = true;
				q.addFirst(w);
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
	}	
	while (!q.isEmpty()) {
		int v = q.removeLast();
		for (int w : G.adj(v)) {
			if (!marked_[w]) {
				edgeTo_[w] = v;
				distTo_[w] = distTo_[v] + 1;
				marked_[w] = true;
				q.addFirst(w);
			}
		}
	}
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
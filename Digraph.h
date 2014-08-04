/***************************************************************
* The Digraph class represents a directed graph of vertices
* named 0 through V.
* It supports the following two primary operations: add an edge
* to the digraph, iterate over all of the vertices adjacent from
* a given vertex.
* Parallel edges and self-loops are permitteed.
*
* This implementation uses an adjacency-lists representation, 
* which is a vertex-indexed array of Bag objects.
* All oeprations take constant time (in the worst case) except
* iterating over the vertices adjacent from a given vertex, which
* takes time proportional to the number of such vertices.
*
* For additional documentation, see Section 4.2 of Algorithms 4th
* Edition, by Robert Sedgewick and Kevin Wayne.
****************************************************************/

#include <Bag\Bag\Bag.h>

class Digraph {
public:
	Digraph();
	Digraph(int V);
	Digraph(std::istream& input);
	~Digraph();
	Digraph(const Digraph& G);
	Digraph& operator=(const Digraph& G);

	int V();
	int E();
	void addEdge(int v, int w);
	Bag<int>* adj(int v);
	Digraph reverse();
	friend std::ostream& operator<<(std::ostream& output, const Digraph& G);

private:
	int V_;			// Vertices
	int E_;			// Edges
	Bag<int>* adj_;	// Adjacency array of bags
};
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
	Digraph();								// Empty constructor
	Digraph(int V);							// Constructor for V verticies
	Digraph(std::istream& input);			// Constructor from input stream
	~Digraph();								// Destructor
	Digraph(const Digraph& G);				// Copy constructor
	Digraph& operator=(const Digraph& G);	// Copy assignment operator

	int V();								// Returns number of verticies
	int E();								// Returns number of edges
	void addEdge(int v, int w);				// Adds an edge between vertex v and w
	Bag<int> adj(int v);					// Returns the vertices adjacent to vertex v
	Digraph reverse();						// Returns the reverse of the digraph
	friend std::ostream& operator<<(std::ostream& output, const Digraph& G);

private:
	int V_;			// Vertices
	int E_;			// Edges
	Bag<int>* adj_;	// Adjacency array of bags
};
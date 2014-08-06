/*************************************************************************
*  Compilation:  javac BreadthFirstDirectedPaths.java
*  Execution:    java BreadthFirstDirectedPaths V E
*  Dependencies: Digraph.java Queue.java Stack.java
*
*  Run breadth first search on a digraph.
*  Runs in O(E + V) time.
*
*  % java BreadthFirstDirectedPaths tinyDG.txt 3
*  3 to 0 (2):  3->2->0
*  3 to 1 (3):  3->2->0->1
*  3 to 2 (1):  3->2
*  3 to 3 (0):  3
*  3 to 4 (2):  3->5->4
*  3 to 5 (1):  3->5
*  3 to 6 (-):  not connected
*  3 to 7 (-):  not connected
*  3 to 8 (-):  not connected
*  3 to 9 (-):  not connected
*  3 to 10 (-):  not connected
*  3 to 11 (-):  not connected
*  3 to 12 (-):  not connected
*
*************************************************************************/

/*************************************************************
* The BreatdthDirectedFirstPaths class represents a data type
* for finding shortest paths (number of edges) from a source
* vertex s (or set of source vertices) to every other vertex 
* in the digraph.
*
* This implementation uses breadth-first search.
* The constructor takes time proportional to V + E,
* where V is the number of vertices and E is the number of edges.
* It uses extra space (not including the digraph) proportional
* to V.
*
* For additional documentation, see Section 4.1 of Algorithms, 
* 4th edition by Robert Sedgewick and Kevin Wayne.
*
**************************************************************/
#include "Digraph.h"
#include <limits>

class BreadthFirstDirectedPaths {
public:
	BreadthFirstDirectedPaths();
	BreadthFirstDirectedPaths(Digraph G, int s);
	BreadthFirstDirectedPaths(Digraph G, Bag<int> sources);
	void bfs(Digraph G, int s);


private:
	const int INF = std::numeric_limits<int>::max();
	bool* marked_;
	int* edgeTo_;
	int* distTo_;
};
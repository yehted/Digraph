/**
*  The <tt>DirectedCycle</tt> class represents a data type for
*  determining whether a digraph has a directed cycle.
*  The <em>hasCycle</em> operation determines whether the digraph has
*  a directed cycle and, and of so, the <em>cycle</em> operation
*  returns one.
*  <p>
*  This implementation uses depth-first search.
*  The constructor takes time proportional to <em>V</em> + <em>E</em>
*  (in the worst case),
*  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
*  Afterwards, the <em>hasCycle</em> operation takes constant time;
*  the <em>cycle</em> operation takes time proportional
*  to the length of the cycle.
*  <p>
*  See {@link Topological} to compute a topological order if the
*  digraph is acyclic.
*  <p>
*  For additional documentation, see <a href="/algs4/42digraph">Section 4.2</a> of
*  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
*
*  @author Robert Sedgewick
*  @author Kevin Wayne
*/

#include <Deque\Deque\Deque.h>
#include "Digraph.h"

class DirectedCycle{
public:
	DirectedCycle();
	DirectedCycle(const Digraph& G);
	bool hasCycle();
	Deque<int> cycle();

private:
	void dfs(const Digraph& G, int v);
	bool check(const Digraph& G);

	bool* marked_;		// marked[v] = has vertex v been marked?
	int* edgeTo_;		// edgeTo[v] = previous vertex on path to v
	bool* onStack_;		// onStack[v] = is vertex on stack?
	Deque<int> cycle_;	// directed cycle (or empty if no such cycle)
};
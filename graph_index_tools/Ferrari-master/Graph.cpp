/**
 * Ferrari Reachability Index<br/>
 * (c) 2012 Stephan Seufert. Web site: http://www.mpi-inf.mpg.de/~sseufert<br/>
 * This work is licensed under the Creative Commons  Attribution-Noncommercial-Share Alike 3.0
 * Unported License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to Creative Commons,
 * 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 * @file Graph.cpp
 * @author Stephan Seufert
 * @date 2012/10/31
 */
//--------------------------------------------------------------------------------------------------
#include "Graph.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string.h>
//--------------------------------------------------------------------------------------------------
/**
 * Constructor
 * @param filename file containing adjacency lists
 */
//--------------------------------------------------------------------------------------------------
Graph::Graph(const std::string& filename) :
    n(0), m(0) {
  std::string line;
  std::ifstream stream(filename.c_str());
  if (!stream.eof()) {
    getline(stream, line);
    std::istringstream iss(line, std::istringstream::in);
    iss >> n >> m;
    nb = std::vector<std::vector<unsigned> >(n);
    pd = std::vector<std::vector<unsigned> >(n);
    deg = std::vector<unsigned>(n, 0);
    for (unsigned i = 0; i < n; ++i)
      deg[i] = 0;
    indeg = std::vector<unsigned>(n, 0);
    leaves = std::deque<unsigned>();
    unsigned s, t, d;
    std::vector<bool> is_root(n, true);
    getline(stream, line);
    while (stream.good()) {
      iss.clear();
      iss.str(line);
      iss >> s;
      d = 0;
      while (iss >> t) {
        // std::cout << s << " -> " << t << std::endl;
        nb[s].push_back(t);
        pd[t].push_back(s);
        ++d;
        ++indeg[t];
        is_root[t] = false;
      }
      assert(s < n);
      deg[s] = d;
      getline(stream, line);
    }
    for (unsigned i = 0; i < n; ++i) {
      if (!deg[i]) {
        leaves.push_back(i);
      }
      if (is_root[i]) {
        roots.push_back(i);
      }
    }
  }
}
//--------------------------------------------------------------------------------------------------
/**
 * Destructor
 */
//--------------------------------------------------------------------------------------------------
Graph::~Graph() {
}
//--------------------------------------------------------------------------------------------------
/**
 * Accessor for adjacency lists
 *
 * @param v vertex
 * @return adjacency list (std::vector)
 */
//--------------------------------------------------------------------------------------------------
const std::vector<unsigned>* Graph::get_neighbors(unsigned v) const {
  return &nb[v];
}
//--------------------------------------------------------------------------------------------------
/**
 * Accessor for root vertices
 *
 * @return roots of the graph (vertices with zero indegree)
 */
//--------------------------------------------------------------------------------------------------
std::vector<unsigned>* Graph::get_roots() {
  return &roots;
}
//--------------------------------------------------------------------------------------------------

/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph &graph) {
  // TODO: YOUR CODE HERE
  vector<Vertex> vertices = graph.getVertices();
  vector<Edge> edges = graph.getEdges();
  queue<Vertex> q;
  for (size_t i = 0; i < vertices.size(); i++) {
    graph.setVertexLabel(vertices[i], "UNEXPLORED");
  }
  for (size_t i = 0; i < edges.size(); i++) {
    Vertex u = edges[i].source;
    Vertex w = edges[i].dest;
    graph.setEdgeLabel(u, w, "UNEXPLORED");
  }
  q.push(vertices[0]);
  graph.setVertexLabel(vertices[0], "VISITED");
  Vertex start = (graph.getAdjacent(vertices[0]))[0];
  int minweight = graph.getEdgeWeight(vertices[0], start);
  Vertex v1 = vertices[0];
  Vertex v2 = start;
  vector<Vertex> adjacent;
  while (!q.empty()) {
    Vertex w = q.front();
    q.pop();
    adjacent = graph.getAdjacent(w);
    for (size_t i = 0; i < adjacent.size(); i++) {
      int currweight;
      if (graph.getVertexLabel(adjacent[i]) == "UNEXPLORED") {
        graph.setVertexLabel(adjacent[i], "VISITED");
        graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
        currweight = graph.getEdgeWeight(w, adjacent[i]);
        if (currweight < minweight){
          minweight = currweight;
          v1 = w;
          v2 = adjacent[i];
        }
        q.push(adjacent[i]);
      }

      else if (graph.getEdgeLabel(w, adjacent[i]) == "UNEXPLORED") {
        graph.setEdgeLabel(w, adjacent[i], "CROSS");
        currweight = graph.getEdgeWeight(adjacent[i], w);
        if (currweight < minweight) {
          minweight = currweight;
          v1 = w;
          v2 = adjacent[i];
        }
      }

    }
  }
  graph.setEdgeLabel(v1, v2, "MIN");
  return minweight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph &graph, Vertex start, Vertex end) {
  // TODO: YOUR CODE HERE
  /* Your code here! */
  vector<Vertex> vertices = graph.getVertices();
  vector<Edge> edges = graph.getEdges();
  queue<Vertex> q;
  unordered_map<Vertex, Vertex> parent;
  int dist = 0;

  for (size_t i = 0; i < vertices.size(); i++) {
    graph.setVertexLabel(vertices[i], "UNEXPLORED");
  }
  for (size_t i = 0; i < edges.size(); i++) {
    Vertex u = edges[i].source;
    Vertex w = edges[i].dest;
    graph.setEdgeLabel(u, w, "UNEXPLORED");
  }

  q.push(start);
  graph.setVertexLabel(start, "VISITED");
  while (!q.empty()) {
    Vertex w = q.front();
    q.pop();
    vector<Vertex> adjacent = graph.getAdjacent(w);

    for (size_t i = 0; i < adjacent.size(); i++) {
      if (graph.getVertexLabel(adjacent[i]) == "UNEXPLORED") {
        graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
        graph.setVertexLabel(adjacent[i], "VISITED");
        pair<Vertex, Vertex> v_pair(adjacent[i], w);
        parent.insert(v_pair);
        q.push(adjacent[i]);
      }
      else if (graph.getEdgeLabel(w, adjacent[i]) == "UNEXPLORED") {
        graph.setEdgeLabel(w, adjacent[i], "CROSS");
      }
    }
  }

  while (start != end) {
    dist++;
    graph.setEdgeLabel(end, parent[end], "MINPATH");
    end = parent[end];
  }

  return dist;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph &graph) {
  vector<Vertex> vertices = graph.getVertices();
  vector<Edge> edges = graph.getEdges();
  DisjointSets vertices_set;
  int vertices_size = vertices.size();
  int edges_size = edges.size();
  int x = 0;
  vertices_set.addelements(vertices_size);
  std::sort(edges.begin(), edges.end(), sort_Edge);

  std::unordered_map<Vertex, int> vertexKeys;
  DisjointSets vertexSets;
  for (size_t i=0; i<vertices.size(); i++) {
      vertexKeys.insert(make_pair(vertices.at(i), i));
      vertexSets.addelements(1);
  }

  for (int i = 0; i < edges_size && x < vertices_size; i++) {
    int u = vertexSets.find(vertexKeys[edges.at(i).source]);
    int w = vertexSets.find(vertexKeys[edges.at(i).dest]);;
    if (vertices_set.find(u) != vertices_set.find(w)) {
      vertices_set.setunion(u, w);
      graph.setEdgeLabel(edges.at(i).source, edges.at(i).dest, "MST");
      x++;
    }
  }
}
bool GraphTools::sort_Edge(Edge u, Edge w){
  return (u.getWeight() < w.getWeight()) ? true : false;
}

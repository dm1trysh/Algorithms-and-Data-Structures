#include <iostream>
#include <limits>
#include <vector>

static constexpr int64_t kInfinity = std::numeric_limits<int64_t>::max();

struct Edge {
  int64_t to_vertex;
  int64_t flow;
  int64_t capacity;

  int64_t CurrentCapacity() const { return capacity - flow; }

  Edge(int64_t to_vertex, int64_t capacity)
      : to_vertex(to_vertex), flow(0), capacity(capacity) {}
};

std::vector<std::vector<int64_t>> graph;
std::vector<Edge> edges;
size_t number;
size_t m_edge;

void AddEdge(int64_t from, int64_t to, int64_t capacity) {
  edges.emplace_back(to, capacity);
  graph[from].emplace_back(edges.size() - 1);
  edges.emplace_back(from, 0);
  graph[to].emplace_back(edges.size() - 1);
}

int64_t FindIncreasingPath(std::vector<int64_t>& used, int64_t phase,
                           int64_t vert, int64_t finish, int64_t min) {
  if (finish == vert) {
    return min;
  }
  used[vert] = phase;
  for (int64_t edge_id : graph[vert]) {
    if (edges[edge_id].CurrentCapacity() == 0) {
      continue;
    }
    if (used[edges[edge_id].to_vertex] == phase) {
      continue;
    }
    int64_t delta =
        FindIncreasingPath(used, phase, edges[edge_id].to_vertex, finish,
                           std::min(min, edges[edge_id].CurrentCapacity()));
    if (delta > 0) {
      edges[edge_id].flow += delta;
      edges[edge_id ^ 1].flow -= delta;
      return delta;
    }
  }
  return 0;
}

int64_t MaxFlow(std::vector<std::vector<int64_t>>& graph,
                std::vector<Edge>& edges, int64_t start, int64_t finish) {
  std::vector<int64_t> used(graph.size(), 0);
  int64_t phase = 1;
  while (FindIncreasingPath(used, phase, start, finish, kInfinity) != 0) {
    ++phase;
  }

  int64_t result = 0;
  for (int64_t i = 0; i < static_cast<int64_t>(graph[start].size()); ++i) {
    result += edges[graph[start][i]].flow;
  }
  return result;
}

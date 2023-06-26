// Maximum Bipartite Matching

#include <stdint.h>

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

class Graph {
 public:
  Graph(size_t left_sz, size_t right_sz)
      : graph_(left_sz + right_sz + 2, std::vector<int64_t>()),
        left_size(left_sz),
        rigth_size(right_sz) {}

  void AddEdge(int64_t from, int64_t to, int64_t capacity) {
    edges_.emplace_back(to, capacity);
    graph_[from].emplace_back(edges_.size() - 1);
    edges_.emplace_back(from, 0);
    graph_[to].emplace_back(edges_.size() - 1);
  }

  int64_t MaxBipartiteMatching(
      int64_t start, int64_t finish,
      std::vector<std::pair<int64_t, int64_t>> matching_edges) {
    int64_t max_flow = MaxFlow(start, finish);

    for (int64_t from = 0; from < left_size; ++from) {
      for (auto edge : graph_[from]) {
        int64_t capacity = edges_[edge].capacity;
        int64_t flow = edges_[edge].flow;
        int64_t to = edges_[edge].to_vertex;
        if (capacity > 0 && flow > 0) {
          matching_edges.push_back({from, to});
        }
      }
    }
  }

 private:
  int64_t FindIncreasingPath(std::vector<int64_t>& used, int64_t phase,
                             int64_t vert, int64_t finish, int64_t min) {
    if (finish == vert) {
      return min;
    }
    used[vert] = phase;
    for (int64_t edge_id : graph_[vert]) {
      if (edges_[edge_id].CurrentCapacity() == 0) {
        continue;
      }
      if (used[edges_[edge_id].to_vertex] == phase) {
        continue;
      }
      int64_t delta =
          FindIncreasingPath(used, phase, edges_[edge_id].to_vertex, finish,
                             std::min(min, edges_[edge_id].CurrentCapacity()));
      if (delta > 0) {
        edges_[edge_id].flow += delta;
        edges_[edge_id ^ 1].flow -= delta;
        return delta;
      }
    }
    return 0;
  }

  int64_t MaxFlow(int64_t start, int64_t finish) {
    std::vector<int64_t> used(graph_.size(), 0);
    int64_t phase = 1;
    while (FindIncreasingPath(used, phase, start, finish, kInfinity) != 0) {
      ++phase;
    }

    int64_t result = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(graph_[start].size()); ++i) {
      result += edges_[graph_[start][i]].flow;
    }
    return result;
  }

  std::vector<std::vector<int64_t>> graph_;
  std::vector<Edge> edges_;
  size_t left_size;
  size_t rigth_size;
};

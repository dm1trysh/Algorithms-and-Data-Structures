//Dinic's algorithm with deleting bypass

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

static constexpr int kInfinity = std::numeric_limits<int>::max();

enum { White, Grey, Black };

struct Edge {
  int from;
  int to;
  int64_t flow;
  int64_t capacity;

  Edge(int from, int to, int64_t capacity)
      : from(from), to(to), flow(0), capacity(capacity) {}

  Edge(int from, int to, int64_t flow, int64_t capacity)
      : from(from), to(to), flow(flow), capacity(capacity) {}
};

class Graph {
 public:
  Graph(size_t n) : graph_(n, std::vector<size_t>()) {}

  void AddEdge(int from, int to, int64_t capacity) {
    edges_.emplace_back(from, to, capacity);
    size_t edge_id = edges_.size() - 1;
    edges_.emplace_back(to, from, 0);
    size_t back_edge_id = edges_.size() - 1;
    graph_[from].push_back(edge_id);
    graph_[to].push_back(back_edge_id);
  }

  bool BFS(size_t start, size_t end) {
    dist_.assign(graph_.size(), kInfinity);
    std::queue<size_t> queue;
    dist_[start] = 0;
    queue.push(start);
    while (!queue.empty() && dist_[end] == kInfinity) {
      size_t vertex = queue.front();
      queue.pop();
      for (size_t i = 0; i < graph_[vertex].size(); ++i) {
        size_t id = graph_[vertex][i];
        if (dist_[edges_[id].to] == kInfinity &&
            edges_[id].flow < edges_[id].capacity) {
          queue.push(edges_[id].to);
          dist_[edges_[id].to] = dist_[edges_[id].from] + 1;
        }
      }
    }
    return dist_[end] != kInfinity;
  }

  int64_t DFS(std::vector<char>& colors, size_t vertex, size_t end,
              int64_t current_flow, std::vector<size_t>& ptr) {
    if (current_flow <= 0) {
      return 0;
    }
    if (vertex == end) {
      return current_flow;
    }
    colors[vertex] = Grey;
    for (size_t id = ptr[vertex]; id < graph_[vertex].size(); ++id) {
      size_t to_id = graph_[vertex][id];
      size_t to = edges_[to_id].to;
      if (colors[to] == White && dist_[to] == dist_[vertex] + 1) {
        int64_t flow = DFS(
            colors, to, end,
            std::min(current_flow, edges_[to_id].capacity - edges_[to_id].flow),
            ptr);
        if (flow > 0) {
          edges_[to_id].flow += flow;
          edges_[to_id ^ 1].flow -= flow;
          colors[vertex] = Black;
          return flow;
        }
      }
    }
    ptr[vertex]++;
    colors[vertex] = Black;
    return 0;
  }

  int64_t DinicAlgo(size_t start, size_t end) {
    int64_t flow = 0;
    while (BFS(start, end)) {
      int64_t delta = 0;
      std::vector<size_t> ptr(graph_.size(), 0);
      do {
        std::vector<char> colors(graph_.size(), White);
        delta = DFS(colors, start, end, kInfinity, ptr);
        flow += delta;
      } while (delta > 0);
    }
    return flow;
  }

  void PrintGraph() {
    std::cout << DinicAlgo(0, graph_.size() - 1) << "\n";
    for (size_t edge_id = 0; edge_id < edges_.size(); edge_id += 2) {
      std::cout << edges_[edge_id].flow << "\n";
    }
  }

 private:
  std::vector<Edge> edges_;
  std::vector<std::vector<size_t>> graph_;
  std::vector<int> dist_;
};

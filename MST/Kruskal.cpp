#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class DST {
 public:
  DST(int64_t n) : parent_(n), rank_(n, 0) {
    for (int64_t i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  bool IsSame(int64_t u, int64_t v) { return Find(u) == Find(v); }

  int64_t Find(int64_t v) {
    if (parent_[v] == v) return v;
    parent_[v] = Find(parent_[v]);
    return parent_[v];
  }

  void Union(int64_t u, int64_t v) {
    int64_t root_u = Find(u);
    int64_t root_v = Find(v);
    if (root_u != root_v) {
      if (rank_[root_u] < rank_[root_v]) {
        std::swap(root_v, root_u);
      }
      parent_[root_v] = root_u;
      if (rank_[root_u] == rank_[root_v]) {
        rank_[root_u] += 1;
      }
    }
  }

 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
};

struct Edge {
  int64_t from;
  int64_t to;
  int64_t weight;
};

std::vector<Edge> MSTKruscal(int64_t n, std::vector<Edge>& edges) {
  std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
  });

  DST dst_vertexes(n);
  std::vector<Edge> answer;
  answer.reserve(n - 1);
  int64_t founded = 0;
  for (auto& edge : edges) {
    if (!dst_vertexes.IsSame(edge.from, edge.to)) {
      ++founded;
      dst_vertexes.Union(edge.from, edge.to);
      answer.push_back(edge);
    }
    if (founded == n - 1) {
      break;
    }
  }
  return answer;
}

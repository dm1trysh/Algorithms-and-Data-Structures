// DSU with ranking heuristic and path compression heuristic

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class DSU {
 public:
  DSU(int64_t n) : parent_(n), rank_(n, 0) {
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

  void Union(int64_t u, int64_t v, int64_t weight) {
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

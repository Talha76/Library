// tested by: https://judge.yosupo.jp/problem/unionfind
struct DSU {
  vector<int> parent;
  vector<int> Size;

  DSU(int n):parent(vector<int>(n)), Size(vector<int>(n, 1)) { iota(all(parent), 0); }

  int find(int i) { return parent[i] == i ? i : parent[i] = find(parent[i]); }

  void merge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return;
    if(Size[u] < Size[v]) swap(u, v);
    parent[v] = u;
    Size[u] += Size[v];
  }
};

namespace DSU {
  vector<int> parent;
  vector<int> Size;

  void init(int n) {
    parent = Size = vector<int>(n, 1);
    iota(all(parent), 0);
  }

  int find(int i) { return parent[i] == i ? i : parent[i] = find(parent[i]); }

  void merge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return;
    if(Size[u] < Size[v]) swap(u, v);
    parent[v] = u;
    Size[u] += Size[v];
  }
};


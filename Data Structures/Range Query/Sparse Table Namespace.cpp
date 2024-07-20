// tested by: https://judge.yosupo.jp/problem/staticrmq
// 0-based indexing, query finds in range [first, last]
inline int lg(int x) { return x ? 31 - __builtin_clz(x) : -1; }
namespace sparse_table {
  using DT = int;
  vector<vector<DT>> table;
  DT f(DT p1, DT p2) { return min(p1, p2); }

  // Call init first
  void init(vector<DT> const &a) {
    int n = a.size(), k = lg(n);
    for(int i = 0; i < n; i++)
      table[i][0] = a[i];
    for(int j = 1; j <= k; j++) {
      for(int i = 0; i + (1<<j) <= n; i++)
        table[i][j] = f(table[i][j - 1], table[i + (1<<(j - 1))][j - 1]);
    }
  }

  int query(int l, int r) {
    int d = lg(r-l+1);
    return f(table[l][d], table[r - (1<<d) + 1][d]);
  }
}

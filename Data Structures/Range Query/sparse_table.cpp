// tested by: https://judge.yosupo.jp/problem/staticrmq

// 0-based indexing, query finds in range [first, last]
namespace sparse_table {
#define __lg(x) (31 - __builtin_clz(x))
  int n;
  vector<vector<int>> table;

  int f(int p1, int p2) { return min(p1, p2); }

  void build(vector<int> &a) {
    n = a.size(); table.assign(n, vector<int>(__lg(n) + 1));
    for(int i = 0; i < n; i++) table[i][0] = a[i];
      int lg = __lg(n) + 1;
    for(int j = 1; j < lg; j++) {
      for(int i = 0; i + (1<<j) <= n; i++)
        table[i][j] = f(table[i][j - 1], table[i + (1<<(j - 1))][j - 1]);
    }
  }

  int query(int l, int r) {
    int d = r - l + 1;
    int ret = INT_MAX;
    int lg = __lg(d);

    // overlapping queries
    ret = f(table[l][lg], table[r - (1<<lg) + 1][lg]);

    // Non-overlapping queries
    for(int i = 0; i <= lg; l += ((d>>i)&1)*(1<<i), i++)
      if((d >> i) & 1)
        ret = f(ret, table[l][i]);
    
    return ret;
  }
};

#define __lg(x) (31 - __builtin_clz(x))
// 0-based indexing, query finds in range [first, last]
template<typename T> struct sparse_table {
  int n;
  vector<T> a;
  vector<vector<T>> table;

  sparse_table(vector<T> &a) : n(a.size()), table(n, vector<T>(__lg(n) + 1)) { this->a=a; build(); }
  T query(int l, int r) {
    int d = r - l + 1;
    T ret = INT_MAX;
    int lg = __lg(d);

    // overlapping queries
    ret = f(table[l][lg], table[r - (1<<lg) + 1][lg]);

    // Non-overlapping queries
    for(int i = 0; i <= lg; l += ((d>>i)&1)*(1<<i), i++)
      if((d >> i) & 1)
        ret = f(ret, table[l][i]);
    
    return ret;
  }

private:
  T f(T p1, T p2) { return min(p1, p2); }
  void build() {
    for(int i = 0; i < n; i++) table[i][0] = a[i];
      int lg = __lg(n) + 1;
    for(int j = 1; j < lg; j++) {
      for(int i = 0; i + (1<<j) <= n; i++)
        table[i][j] = f(table[i][j - 1], table[i + (1<<(j - 1))][j - 1]);
    }
  }
};


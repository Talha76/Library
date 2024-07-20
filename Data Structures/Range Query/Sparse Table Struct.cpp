inline int lg(int x) { return x ? 31 - __builtin_clz(x) : -1; } 
// 0-based indexing, query finds in range [first, last]
template<typename T> struct sparse_table {
  int n;
  vector<vector<T>> table;
  function<T(T,T)> f;

  sparse_table(vector<T> &a, function<T(T,T)> _f) : n(a.size()), table(n, vector<T>(lg(n) + 1)), f(_f) {
    for(int i = 0; i < n; i++) table[i][0] = a[i];
    int d = lg(n) + 1;
    for(int j = 1; j < d; j++)
      for(int i = 0; i + (1<<j) <= n; i++)
        table[i][j] = f(table[i][j - 1], table[i + (1<<(j - 1))][j - 1]);
  }
  T query(int l, int r) {
    int d = lg(r-l+1);
    return f(table[l][d], table[r+1 - (1<<d)][d]);
  }
};

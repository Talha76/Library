#include "bits/stdc++.h"
using namespace std;

#define __lg(x) (31 - __builtin_clz(x))
// 0-based indexing, query finds in range [first, last)
template<typename T> struct sparse_table {
  int n;
  vector<T> a;
  vector<vector<T>> table;

  sparse_table(int n, vector<T> &a) : n(n), table(n, vector<T>(__lg(n) + 1)) { this->a=a; build(); }
  T query(int l, int r) {
    int d = r - l;
    T ret = INT_MAX;
    int lg = __lg(d);

    // overlapping queries
    ret = f(table[l][lg], table[r - (1<<lg)][lg]);

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

// Solves: https://www.spoj.com/problems/RMQSQ/
int main() {
	int n;
  cin >> n;
  vector<int> a(n);
  for(auto &i : a)
    cin >> i;

  int q;
  cin >> q;
  sparse_table<int> st(n, a);
  while(q--) {
    int l, r;
    cin >> l >> r;
    cout << st.query(l, ++r) << "\n";
  }
}

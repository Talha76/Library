#include "bits/stdc++.h"
using namespace std;
// Solves: https://lightoj.com/problem/horrible-queries

template <class T>
struct lazy_seg {
  vector<T> Tree, prop;
  lazy_seg() {}
  lazy_seg(vector<T> &a) : Tree(vector<T>(4*a.size())), prop(vector<T>(4*a.size())) { build(1, a.size() - 1, a); }

  T build(int l, int r, vector<T> &a, int n = 1) {
    if(l == r) return Tree[n] = a[l];
    int m = (l + r) >> 1;
    return Tree[n] = f(build(l, m, a, 2*n), build(m + 1, r, a, 2*n + 1));
  }

  T update(int i, int j, T x, int l, int r, int node = 1) {
    if(i > r or j < l) return Tree[node];
    if(i <= l and r <= j) {
      prop[node] += x;
      return Tree[node] += (r - l + 1) * x;
    }
    int m = (r + l)/2;
    return Tree[node] = f(update(i, j, x, l, m, node*2), update(i, j, x, m + 1, r, node*2 + 1)) + (r - l + 1) * prop[node];
  }

  T query(int i, int j, int l, int r, T carry = 0, int node = 1) {
    if(i > r or j < l) return 0;
    if(i <= l and r <= j) {
      return carry * (r - l + 1) + Tree[node];
    }
    int m = (l + r)/2;
    return f(query(i, j, l, m, carry + prop[node], node*2), query(i, j, m + 1, r, carry + prop[node], node*2 + 1));
  }

private:
  T f(T x, T y) { return x + y; }
};

void magic() {
  int n, q;
  cin >> n >> q;
  lazy_seg<long long> seg;
  seg.Tree.assign(4*n, 0);
  seg.prop.assign(4*n, 0);

  int c, l, r, v;
  while(q--) {
    cin >> c >> l >> r;
    l++; r++;
    if(c) {
      cout << seg.query(l, r, 1, n) << "\n";
    } else {
      cin >> v;
      seg.update(l, r, v, 1, n);
    }
  }
}

int32_t main() {
  cin.tie(NULL)->sync_with_stdio(false);

  int T, kase = 0;
  cin >> T;
  while(T--) {
    cout << "Case " << ++kase << ":\n";
    magic();
  }

  return 0;
}

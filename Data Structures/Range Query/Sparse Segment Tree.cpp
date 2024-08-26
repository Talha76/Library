// Then which of Allah's favor will you deny?
// author: MushfiqTalha
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

namespace segtree {
  using DT = int;
  int L, R;
  DT identity;
  vector<DT> val;
  vector<int> lt, rt;

  DT merge(const DT &a, const DT &b) { return a+b; }
  void apply(int u, const DT &uval, int l, int r) { val[u] += uval; }

  /* Don't touch anything below */
  int new_node(const DT& v=identity) {
    int new_number = val.size();
    val.emplace_back(v);
    lt.push_back(0); rt.push_back(0);
    return new_number;
  }
  void update(int i, DT const U, int l=L, int r=R, int u=0) {
    if (i > r or i < l) return;
    if (i == l and i == r) {
      apply(u, U, l, r);
      return;
    }
    int m = l+r >> 1;
    if (not lt[u]) lt[u] = new_node();
    if (not rt[u]) rt[u] = new_node();
    update(i, U, l, m, lt[u]);
    update(i, U, m+1, r, rt[u]);
    val[u] = merge(val[lt[u]], val[rt[u]]);
  }
  DT query(int ql, int qr, int l=L, int r=R, int u=0) {
    if (ql > r or qr < l) return identity;
    if (ql <= l and r <= qr) return val[u];
    int m = l+r >> 1;
    if (not lt[u]) lt[u] = new_node();
    if (not rt[u]) rt[u] = new_node();
    return merge(query(ql, qr, l, m, lt[u]),
        query(ql, qr, m+1, r, rt[u]));
  }
  void init(int _L, int _R, DT _identity) {
    identity = _identity;
    L = _L, R = _R;
    new_node();
  }
}
 
int main() {
  cin.tie(NULL)->sync_with_stdio(false);
 
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  segtree::init(1, 1e9, 0);
  for (auto &e: a) cin >> e, segtree::update(e, 1);

  for (int k, x; q--;) {
    char t;
    cin >> t >> k >> x;
    if (t == '?') cout << segtree::query(k, x) << '\n';
    else {
      k--;
      segtree::update(a[k], -1);
      segtree::update(x, 1);
      a[k] = x;
    }
  }
 
  return 0;
}

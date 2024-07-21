namespace persistent_segtree {
  using DT = int;

  int L, R;
  DT identity;
  vector<DT> val;
  vector<int> roots, lt, rt;

  DT merge(const DT &a, const DT &b) { return a+b; }

  int new_node(const DT& v=identity) {
    int new_number = val.size();
    val.emplace_back(v);
    lt.push_back(0); rt.push_back(0);
    return new_number;
  }

  /* Don't touch anything below */
  void init(int _L, int _R, DT _identity) {
    identity = _identity;
    L = _L, R = _R;
    roots.push_back(new_node());
  }

  int update(int i, int l=L, int r=R, int u=roots.back()) {
    if (i > r or i < l) return u;
    if (i == l and i == r) return new_node(val[u] + 1);
    int m = l+r >> 1;
    int new_lt = update(i, l, m, lt[u]);
    int new_rt = update(i, m+1, r, rt[u]);
    u = new_node();
    lt[u] = new_lt, rt[u] = new_rt;
    val[u] = merge(val[lt[u]], val[rt[u]]);
    return u;
  }

  int query(int ql, int qr, int u, int l=L, int r=R) {
    if (ql > r or qr < l) return identity;
    if (ql <= l and r <= qr) return val[u];
    int m = l+r >> 1;
    return merge(query(ql, qr, lt[u], l, m),
        query(ql, qr, rt[u], m+1, r));
  }
}

template<typename DT> struct segtree {
  const DT I;
  vector<DT> val;
  int L, R;
  void apply(int u, const DT &U) { val[u] = U; }
  DT merge(const DT &a, const DT &b, int l, int r) {
    auto [ans_a, pre_a, suf_a, sum_a] = a;
    auto [ans_b, pre_b, suf_b, sum_b] = b;
    LL ans = max({ans_a, ans_b, suf_a + pre_b}),
       pre = max(pre_a, sum_a + pre_b),
       suf = max(suf_b, sum_b + suf_a),
       sum = sum_a + sum_b;
    return {ans, pre, suf, sum};
  }
  /* -- Do Not Touch Anything Below This -- */
  segtree(vector<DT> v, DT _I, int _L, int _R) : val(v.size()<<2), I(_I), L(_L), R(_R)
  { build(L, R, v); }
  void build(int l, int r, vector <DT> const &v, int u = 1 ) {
    if(l == r) {
      val[u] = v[l];
      return;
    }
    int m = l+r >> 1, lft = u << 1, ryt = lft | 1;
    build(l, m, v, lft);
    build(m+1, r, v, ryt);
    val[u] = merge(val[lft], val[ryt], l, r);
  }
  void update(int i, DT uval, int l = -1, int r = -1, int u = 1) {
    l = ~l ? l : L, r = ~r ? r : R;
    if (i < l or i > r) return;
    if(i == l and i == r) {
      apply(u, uval);
      return;
    }
    int m = l+r >> 1, lft = u << 1, ryt = lft | 1;
    update(i, uval,  l,  m, lft);
    update(i, uval, m+1, r, ryt);
    val[u] = merge(val[lft], val[ryt], l, r);
  }
  DT query(int ql, int qr, int l = -1, int r = -1, int u = 1) {
    l = ~l ? l : L, r = ~r ? r : R;
    if (qr < l or ql > r) return I;
    if (ql <= l and r <= qr) return val[u];
    int m = l+r >> 1, lft = u << 1, ryt = lft | 1;
    DT ansl = query(ql, qr, l, m, lft);
    DT ansr = query(ql, qr, m + 1, r, ryt);
    return merge(ansl, ansr, l, r);
  }
};

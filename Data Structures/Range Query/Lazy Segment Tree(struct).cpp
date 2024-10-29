/*
 * Constructor(array_of_elements, value_identity, none_identity, L, R, apply_fn, lazy_apply_fn, merge_fn)
 *    - apply_fn(val, uval, l, r): applies the update uval with val return returns updated val
 *    - lazy_apply_fn(lz, uval, l, r): applies uval to lazy value 'lz' and returns updated lazy val
 *    - merge_fn(a, b, l, r): merges values a, b
 *
 * ***Important:*** Declare 'I' and 'None' in a local scope
 *                  Declaring these in global scope gives compilation error
 *                  Also use g++20 or later versions
 */
template<typename DT, typename LT, auto I, auto None,
    auto apply, auto apply_fn, auto merge> 
struct segtree {
  vector<DT> val;
  vector<LT> lz;
  int L, R;

  segtree(vector<DT> v, int _L, int _R) : val(v.size()<<2), lz(v.size()<<2),
    L(_L), R(_R) { build(L, R, v); }
  void push(int l, int r, int u) {
    if(l == r) return;
    apply(u << 1, lz[u], l, (l + r) >> 1);
    apply(u << 1 | 1, lz[u], (l + r + 2) >> 1, r);
    lz[u] = None;
  }
  void build(int l, int r, vector <DT> const &v, int u = 1 ) {
    lz[u] = None;
    if(l == r) {
      val[u] = v[l];
      return;
    }
    int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
    build(l, m, v, lft);
    build(m + 1, r, v, ryt);
    val[u] = merge(val[lft], val[ryt], l, r);
  }
  void update(int ql,int qr, LT uval, int l = -1, int r = -1, int u = 1) {
    l = ~l ? l : L, r = ~r ? r : R;
    if (qr < l or ql > r) return;
    if(ql <= l and r <= qr) {
      apply(u, uval, l, r);
      return;
    }
    push(l, r, u);
    int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
    update(ql, qr, uval,  l,  m, lft);
    update(ql, qr, uval, m + 1, r, ryt);
    val[u] = merge(val[lft], val[ryt], l, r);
  }
  DT query(int ql, int qr, int l = -1, int r = -1, int u = 1) {
    l = ~l ? l : L, r = ~r ? r : R;
    if (qr < l or ql > r) return I;
    if (ql <= l and r <= qr) return val[u];
    push(l, r, u);
    int m = (l + r) >> 1, lft = u << 1, ryt = lft | 1;
    DT ansl = query(ql, qr, l, m, lft);
    DT ansr = query(ql, qr, m + 1, r, ryt);
    return merge(ansl, ansr, l, r);
  }
};

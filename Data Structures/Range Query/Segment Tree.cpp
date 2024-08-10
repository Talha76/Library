/*--------------------------------------------------
 * There are six things you need to worry about

    * The data type of the values on the nodes: DT
    * How does the value of a node change
        when a new update comes : apply()
        Merging of updates take place here
    * How to merge the results of two nodes while answering
        queries : merge()
    * What is the identity of merge() : I
        This is the equivalent to answering queries in an empty
        range, a value that will never change the result of an
        answer

 *--------------------------------------------------*/
namespace segtree {
  const int N = 1000006;

  using DT = long long;
  constexpr DT I = 0; 

  DT val[N<<2];
  int L, R;
  void apply(int u, const DT &U) {
    val[u] += U;
  }
  DT merge(const DT &a, const DT &b, int l, int r) {
    return a + b;
  }
  /* -- Do Not Touch Anything Below This -- */

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
  void update(int i, DT uval, int l = L, int r = R, int u = 1) {
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
  DT query(int ql, int qr, int l = L, int r = R, int u = 1) {
    if (qr < l or ql > r) return I;
    if (ql <= l and r <= qr) return val[u];
    int m = l+r >> 1, lft = u << 1, ryt = lft | 1;
    DT ansl = query(ql, qr, l, m, lft);
    DT ansr = query(ql, qr, m + 1, r, ryt);
    return merge(ansl, ansr, l, r);
  }
  void init(int _L, int _R, vector <DT> v) {
    L = _L, R = _R;
    build(L, R, v);
  }
}

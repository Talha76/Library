/*--------------------------------------------------
 * There are six things you need to worry about

    * The data type of the values on the nodes: DT
    * The data type of the updates on the nodes: LT
        Lazy data will be the same as an update
        Lazy data is the update that has ALREADY BEEN 
        PROCESSED on this node, and WILL BE PUSHED down
        to the childred later, value is always updated.
    * How does the value and lazy data of a node change
        when a new update comes : apply()
        Merging of updates take place here
    * How to merge the results of two nodes while answering
        queries : merge()
    * What is the identity of apply() : None
        This is equivalent to "No update", should represent an
        update which changes nothing
    * What is the identity of merge() : I
        This is the equivalent to answering queries in an empty
        range, a value that will never change the result of an
        answer

 *--------------------------------------------------*/
namespace segtree {
  const int N = 1000006;

  using DT = long long;
  using LT = long long;
  constexpr DT I = 0; 
  constexpr LT None = 0;

  DT val[N<<2];
  LT lz[N<<2];
  int L, R;
  void apply(int u, const LT &U, int l, int r) {
    if (U == None) return;
    val[u] += (r - l + 1) * U;
    lz[u] += U;
  }
  DT merge(const DT &a, const DT &b, int l, int r) {
    return a + b;
  }
  /* -- Do Not Touch Anything Below This -- */

  void push(int l, int r, int u) {
    if(l == r) return;
    apply(u << 1, lz[u], l, (l + r) >> 1);
    apply(u << 1 | 1, lz[u], (l + r + 2) >> 1, r);
    lz[u] = None;
  }
  void build(int s, int e, vector <DT> const &v, int u = 1 ) {
    lz[u] = None;
    if(s == e) {
      val[u] = v[s];
      return;
    }
    int m = s+e >> 1, lft = u << 1, ryt = lft | 1;
    build(s, m, v, lft);
    build(m+1, e, v, ryt);
    val[u] = merge(val[lft], val[ryt], s, e);
  }
  void update(int l,int r, LT uval, int s = L, int e = R, int u = 1) {
    if (r < s or l > e) return;
    if(l <= s and e <= r) {
      apply(u, uval, s, e);
      return;
    }
    push(s, e, u);
    int m = s+e >> 1, lft = u << 1, ryt = lft | 1;
    update(l, r, uval,  s,  m, lft);
    update(l, r, uval, m+1, e, ryt);
    val[u] = merge(val[lft], val[ryt], s, e);
  }
  DT query(int l, int r, int s = L, int e = R, int u = 1) {
    if (r < s or l > e) return I;
    if (l <= s and e <= r) return val[u];
    push(s, e, u);
    int m = s+e >> 1, lft = u << 1, ryt = lft | 1;
    DT ansl = query(l, r, s, m, lft);
    DT ansr = query(l, r, m+1, e, ryt);
    return merge(ansl, ansr, s, e);
  }
  void init(int _L, int _R, vector <DT> v) {
    L = _L, R = _R;
    build(L, R, v);
  }
};

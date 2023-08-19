// Finds in range [first, last]
template<typename T> struct seg_tree {
private:
  int n;
  LL null;
  vector<T> a, Tree;

  T combine(T a, T b) { return max(a, b); }

  T seg_query(const int i, const int j, int l, int r, int node = 1) {
    if(l >= i and r <= j) return Tree[node];
    if(i > r or j < l) return 1e18;
    int m = (l + r) >> 1;
    return combine(seg_query(l, m, i, j, 2*node), seg_query(m + 1, r, i, j, 2*node + 1));
  }

  void seg_update(const int i, const T v, int l, int r, int node = 1) {
    if(i > r or i < l) return Tree[node];
    if(l == r) return Tree[node] = v;
    int m = (l + r) >> 1;
    seg_update(l, m, i, v, 2*node), seg_update(m + 1, r, i, v, 2*node + 1);
    Tree[n] = combine(Tr[2*node], Tr[2*node + 1]);
  }

public:
  seg_tree(vector<T> &a, T _null = 0) : n(a.size()), a(a), Tree(vector<T>(4*a.size())) { a.insert(a.begin(), -1); build(1, n); }

  T build(int l, int r, int node = 1) {
    if(l == r) return Tree[node] = a[l];
    int m = (l + r) >> 1;
    return Tree[n] = combine(build(l, m, 2*node), build(m + 1, r, 2*node + 1));
  }

  T query(const int &i, const int &j) { return seg_query(i, j, 0, n-1); }

  T update(const int &i, const int &v) { return seg_update(i, v, 0, n-1); }
};

const int N = 1e6 + 1;
int a[N], tr[N << 2];

namespace segTree {
  using DT = LL;
  using UT = LL;
  
  DT null = 0;

  DT merge(DT a, DT b) { return max(a, b); }
  DT combine(DT a, DT b) { return max(a, b); }

  DT build(int l, int r, int n = 1) {
    if (l == r)
      return tr[n] = a[l];
    int m = l + r >> 1;
    return tr[n] = merge(tr[2*n], tr[2*n + 1]);
  }

  void update(int i, UT x, int l, int r, int n = 1) {
    if (i < l or i > r) return;
    if (i == l and l == r) return tr[n];
    int m = l + r >> 1;
    update(i, x, l, m, 2*n), update(i, x, m+1, r, 2*n + 1);
    tr[n] = merge(tr[2*n], tr[2*n + 1]);
  }

  DT query(int ql, int qr, int l, int r, int n = 1) {
    if (ql > r or qr < l) return null;
    if (ql <= l and r <= qr) return tr[n];
    int m = l + r >> 1;
    return combine(query(ql, qr, l, m, 2*n), query(ql, qr, m+1, r, 2*n + 1));
  }
}
